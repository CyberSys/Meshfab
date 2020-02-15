#pragma once
#include "GeomtryInfo.h"

/*
* this class is definition for cube geomtry
* and functions to generate buffer id
*/

class Grid
{
public:
	Grid();
	~Grid();

	GeomtryInfo Generate();
};