#pragma once

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

	unsigned int vao;
	unsigned int vbo;
	unsigned int nbo;
	unsigned int cbo;
	unsigned int ibo;
};