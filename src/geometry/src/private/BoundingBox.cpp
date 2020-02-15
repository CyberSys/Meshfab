#include "BoundingBox.h"

#include <glew.h>

BoundingBox::BoundingBox() {}

BoundingBox::~BoundingBox() {}

GeomtryInfo BoundingBox::Generate()
{
	GeomtryInfo result;

	GLfloat cube_vertices[] = {
	-0.5, -0.5, -0.5, 1.0,
	 0.5, -0.5, -0.5, 1.0,
	 0.5,  0.5, -0.5, 1.0,
	-0.5,  0.5, -0.5, 1.0,
	-0.5, -0.5,  0.5, 1.0,
	 0.5, -0.5,  0.5, 1.0,
	 0.5,  0.5,  0.5, 1.0,
	-0.5,  0.5,  0.5, 1.0,
	};

	GLuint cube_elements[] = {
	0, 1, 2, 3,
	4, 5, 6, 7,
	0, 4, 1, 5, 2, 6, 3, 7
	};

	glGenVertexArrays(1, &result.vao);
	glBindVertexArray(result.vao);

	glGenBuffers(1, &result.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glGenBuffers(1, &result.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	result.num_vertices = 8;
	result.num_indecies = 4;

	return result;
}
