#include "Model3D.h"
#include "Model.h"

#include <glew.h>

Model3D::Model3D()
{
}

Model3D::~Model3D()
{
}

template <class type>
inline static unsigned int create_gpuBuffer(vector<type> invector)
{
	unsigned int buf_id = 0;
	glGenBuffers(1, &buf_id);
	glBindBuffer(GL_ARRAY_BUFFER, buf_id);
	glBufferData(GL_ARRAY_BUFFER, invector.size() * sizeof(type), invector.data(), GL_DYNAMIC_DRAW);
	return buf_id;
}

vector<GeomtryInfo> Model3D::Generate(const char * filepath)
{
	vector<GeomtryInfo> result;

	auto model_parts = Model::Load(filepath);
	for (auto part : model_parts)
	{
		GeomtryInfo gpubuffers;
		glGenVertexArrays(1, &gpubuffers.vao);
		glBindVertexArray(gpubuffers.vao);

		//vertex buffer
		gpubuffers.vbo = create_gpuBuffer(part.vertices);
		glEnableVertexAttribArray(0); //vertices always 3-comp(x,y,z).
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
		gpubuffers.num_vertices = part.vertices.size() / 3;

		//vertex buffer
		gpubuffers.nbo = create_gpuBuffer(part.normals);
		glEnableVertexAttribArray(1); //nomrals always 3-comp(x,y,z).
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, NULL);

		//remaining pdarts of infos like colors, uvs

		//index buffer
		glGenBuffers(1, &gpubuffers.ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpubuffers.ibo); 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, part.indices.size() * sizeof(unsigned int), part.indices.data(), GL_DYNAMIC_DRAW);
		gpubuffers.num_indecies = part.indices.size();

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//bounding box
		gpubuffers.bmax = part.bounding_max;
		gpubuffers.bmin = part.bounding_min;

		result.push_back(gpubuffers);
	}

	return result;
}
