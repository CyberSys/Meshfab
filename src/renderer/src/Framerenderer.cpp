#include "Framerenderer.h"
#include "GeoShapes/Shape2D.h"

#include <glew.h>

Framerenderer::Framerenderer() {}

Framerenderer::~Framerenderer() {}

void Framerenderer::init()
{
	geometryID = Shape2D::Create_Quad().vao;
}

void Framerenderer::render()
{
	glBindVertexArray(geometryID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
