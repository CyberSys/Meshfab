#pragma once
#include "private/GPUBufferID.h"

class Shape2D
{
public:
	Shape2D();

	~Shape2D();

	static GPUBufferID Create_Quad();
};