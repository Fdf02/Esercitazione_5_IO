#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary{

///\brief Import the Polygonal mesh and test if the mesh is correct
///\param filepath: path of the file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportMesh(const string& filepath, PolygonalMesh& mesh);

///\brief Import the Cell0D properties from Cell0Ds.csv file
///\param filename: name of the file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(const string &filename, PolygonalMesh& mesh);

///\brief Import the Cell1D properties from Cell1Ds.csv file
///\param filename: name of the file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(const string &filename, PolygonalMesh& mesh);

///\brief Import the Cell2D properties from Cell2Ds.csv file
///\param filename: name of the file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(const string &filename, PolygonalMesh& mesh);

}
