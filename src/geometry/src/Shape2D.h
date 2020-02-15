#pragma once
#include "private/GeomtryInfo.h"

class Shape2D
{
public:
	Shape2D();

	~Shape2D();

	static GeomtryInfo Create_Quad();
};