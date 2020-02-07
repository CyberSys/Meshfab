#pragma once
#include <glm.hpp>
#include <vector>
using namespace std;
/*
* this struct for generated buffer on gpu
* after generation will need to hold all buffers id
*/

struct GeomtryInfo
{
	int num_faces;
	int num_edges;
	int num_vertices;
	int num_indecies;
	glm::vec3 bmax;
	glm::vec3 bmin;

	unsigned int vao;
	unsigned int vbo;
	unsigned int nbo;
	unsigned int cbo;
	unsigned int ibo;

	vector<unsigned int> textures_ids;
};