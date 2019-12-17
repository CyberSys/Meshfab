#include "Shape3D.h"
#include "private/Cube.h"

Shape3D::Shape3D() {}

Shape3D::~Shape3D() {}

///////////////////////////////////// Creators

GeomtryInfo Shape3D::Create_Cube()
{
	Cube cube;

	return cube.Generate();
}
