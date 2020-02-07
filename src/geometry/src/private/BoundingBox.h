#pragma once
#include "GeomtryInfo.h"

/*
* this class is definition for BoundingBox geomtry
* and functions to generate buffer id
*/

class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	GeomtryInfo Generate();
};