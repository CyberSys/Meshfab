#pragma once

/*
* this struct for generated buffer on gpu
* after generation will need to hold all buffers id
*/

struct GPUBufferID
{
	unsigned int vao;
	unsigned int vbo;
	int num_vertices;
	int num_faces;
	int num_triangles;
};