#include "StaticModel.h"
#include <glew.h>
StaticModel::StaticModel()
{
}

StaticModel::~StaticModel()
{
}

void StaticModel::draw()
{
	for (auto mesh : meshes)
	{
		Mesh ref = mesh.second;
		glBindVertexArray(ref.vao);
		glDrawArrays(GL_TRIANGLES, 0, ref.mVertices.size() / 3);
	}
}

void StaticModel::setup()
{
	for (auto mesh : meshes)
	{
		Mesh ref = mesh.second;

		glGenVertexArrays(1, &ref.vao);
		glGenBuffers(1, &ref.vbo);
		glGenBuffers(1, &ref.nbo);
		glGenBuffers(1, &ref.tbo);

		glBindVertexArray(ref.vao);
		glBindBuffer(GL_ARRAY_BUFFER, ref.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ref.mVertices[0]) * ref.mVertices.size(), &ref.mVertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, ref.nbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ref.mNormals[0]) * ref.mNormals.size(), &ref.mNormals[0], GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, ref.tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ref.mTexCoords[0]) * ref.mTexCoords.size(), &ref.mTexCoords[0], GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

		mesh.second = ref;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
