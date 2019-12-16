#pragma once
#include "GPUBufferID.h"

/*
* this class is definition for cube geomtry
* and functions to generate buffer id
*/

class Cube
{
public:
	Cube();
	~Cube();

	GPUBufferID Generate();
};