#include "Shape2D.h"
#include "private/Quad.h"

Shape2D::Shape2D()
{
}

Shape2D::~Shape2D()
{
}

GPUBufferID Shape2D::Create_Quad()
{
	Quad quad;

	return quad.Generate();
}
