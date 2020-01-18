#pragma once
#include "private/GeomtryInfo.h"

/*
* this class responsible for generating geomtery 
* buffer and return id for this buffer to use it 
* this class update and create geo buffers.
*/

class Shape3D
{
public:
	Shape3D();

	~Shape3D();

	static GeomtryInfo Create_Cube();
};