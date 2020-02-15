#include "Grid.h"

#include <glew.h>
#include <vector>
using namespace std;

Grid::Grid() {}

Grid::~Grid() {}

inline static void 
CreateGrid(int width, int depth, vector<float>& verts, vector<unsigned int>& indx)
{
	int i = 0;
	int count = 0;

	for (i = -width; i <= width; i++)
	{
		verts.push_back((float)i);
		verts.push_back(0.0f);
		verts.push_back((float)-depth);

		verts.push_back((float)i);
		verts.push_back(0.0f);
		verts.push_back((float)depth);

		verts.push_back((float)-width);
		verts.push_back(0.0f);
		verts.push_back((float)i);

		verts.push_back((float)width);
		verts.push_back(0.0f);
		verts.push_back((float)i);
	}

	int dw = width * depth;
	indx.resize(dw);
	unsigned int* id = &indx[0];
	for (int i = 0; i < width*depth; i += 4)
	{
		*id++ = i;
		*id++ = i + 1;
		*id++ = i + 2;
		*id++ = i + 3;
	}
}

GeomtryInfo Grid::Generate()
{
	GeomtryInfo result;
	vector<float> verts;
	vector<unsigned int> indxs;

	CreateGrid(10,10,verts,indxs);

	glGenVertexArrays(1, &result.vao);
	glBindVertexArray(result.vao);

	glGenBuffers(1, &result.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indxs.size() * sizeof(GLuint), indxs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &result.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec4), verts.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	result.num_vertices = (int)verts.size() / 3;
	result.num_indecies = (int)indxs.size();

	return result;
}
