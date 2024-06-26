#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary {
bool ImportMesh(const string& filepath,
                PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(filepath + "/Cell0Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell0D marker:" << endl;
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
            {
                cout << "\t" << id;
            }

            cout << endl;
        }
    }

    if(!ImportCell1Ds(filepath + "/Cell1Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
            {
                cout << "\t" << id;
            }

            cout << endl;
        }
    }

    if(!ImportCell2Ds(filepath + "/Cell2Ds.csv",
                       mesh))
    {
        return false;
    }
    else
    {
        // Test
        for(unsigned int c = 0; c < mesh.NumberCell2D; c++)
        {
            vector<unsigned int> edges = mesh.Cell2DEdges[c];
            unsigned int ne = edges.size();

            for(unsigned int e = 0; e < ne; e++)
            {
                const unsigned int origin = mesh.Cell1DVertices[edges[e]][0];
                const unsigned int end = mesh.Cell1DVertices[edges[e]][1];

                auto findOrigin = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), origin);
                if(findOrigin == mesh.Cell2DVertices[c].end())
                {
                    cerr << "Wrong mesh" << endl;
                    return 2;
                }

                auto findEnd = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), end);
                if(findEnd == mesh.Cell2DVertices[c].end())
                {
                    cerr << "Wrong mesh" << endl;
                    return 3;
                }

            }
        }
    }
    return true;
}
// ***************************************************************************
 bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);

    if(file.fail())
    {
        return false;
    }

    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        std::replace(line.begin(),line.end(),';',' ');
        listLines.push_back(line);
    }

    file.close();

    listLines.pop_front();

    mesh.NumberCell0D = listLines.size();

    if (mesh.NumberCell0D == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> marker >> coord(0) >> coord(1);

        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)
        {
            if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
            {
                mesh.Cell0DMarkers.insert({marker, {id}});
            }
            else
            {
                mesh.Cell0DMarkers[marker].push_back(id);
            }
        }

    }

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);

    if(file.fail())
    {
        return false;
    }

    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        std::replace(line.begin(),line.end(),';',' ');
        listLines.push_back(line);
    }

    file.close();

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i originend;

        converter >>  id >> marker >> originend(0) >> originend(1);

        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(originend);

        if( marker != 0)
        {
            if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
            {
                mesh.Cell1DMarkers.insert({marker, {id}});
            }
            else
            {
                mesh.Cell1DMarkers[marker].push_back(id);
            }
        }

    }

    return true;
}
// ***************************************************************************
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh)
{
    ifstream file;
    file.open(filename);

    if(file.fail())
    {
        return false;
    }

    list<string> listLines;
    string line;
    while (getline(file, line))
    {
        std::replace(line.begin(),line.end(),';',' ');
        listLines.push_back(line);
    }

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        unsigned int numvertices;
        unsigned int numedges;

        converter >>  id >> marker >> numvertices;
        vector<unsigned int> vertices(numvertices) ;

        for(unsigned int i = 0; i < numvertices; i++)
            converter >> vertices[i];

        converter >> numedges;
        vector<unsigned int> edges(numedges) ;

        for(unsigned int i = 0; i < numedges; i++)
            converter >> edges[i];

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);


        if( marker != 0)
        {
            if (mesh.Cell2DMarkers.find(marker) == mesh.Cell2DMarkers.end())
            {
                mesh.Cell2DMarkers.insert({marker, {id}});
            }
            else
            {
                mesh.Cell2DMarkers[marker].push_back(id);
            }
        }

    }
    file.close();
    return true;
}
}
