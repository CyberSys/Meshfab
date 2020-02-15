#pragma once
#include "GeomtryInfo.h"

#include <vector>
using namespace std;

/*
* this class is definition for Model 3D geomtry
* and functions to generate buffer id
*/

class Model3D
{
public:
	Model3D();
	~Model3D();

	vector<GeomtryInfo> Generate(const char * filepath);
};