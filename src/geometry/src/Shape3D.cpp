#include "Shape3D.h"
#include "private/Cube.h"
#include "private/Model3D.h"
#include "private/Grid.h"
#include "private/BoundingBox.h"

Shape3D::Shape3D() {}

Shape3D::~Shape3D() {}

///////////////////////////////////// Creators

GeomtryInfo Shape3D::Create_Cube()
{
	Cube cube;

	return cube.Generate();
}

vector<GeomtryInfo> Shape3D::Create_Model(const char* filepath)
{
	Model3D model;

	return model.Generate(filepath);
}

GeomtryInfo Shape3D::Create_Grid()
{
	Grid grid;

	return grid.Generate();
}

GeomtryInfo Shape3D::Create_BBox()
{
	BoundingBox bbox;

	return bbox.Generate();
}
