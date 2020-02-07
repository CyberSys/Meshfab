#include "DefaultMaterial.h"
#include "ShaderProgram.h"

DefaultMaterial::DefaultMaterial() {}

DefaultMaterial::~DefaultMaterial() {}

unsigned int DefaultMaterial::Create()
{
	const char* vs = 
		R"CODE( #version 330 core
				layout (location = 0) in vec3 vertex;
				uniform mat4 mvp;
				void main()
				{
					gl_Position = mvp * vec4(vertex, 1.0f);
				})CODE";

	const char* ps = 
		R"CODE( #version 330 core
				out vec4 FragColor;
				void main()
				{
					FragColor = vec4(0.8,0.8,0.8,0.8);
				})CODE";

	ShaderProgram program(vs,ps);

	return program.ID;
}


////***********************
//// checkhoard shader ****
////***********************
/*
unsigned int ColoredMaterial::Create()
{
	const char* vs =
		R"CODE( #version 330 core
				layout (location = 0) in vec3 vertex;

				uniform mat4 mvp;

				out vec3 vert;
				void main()
				{
					gl_Position = mvp * vec4(vertex, 1.0f);
					vert = vertex;
				})CODE";

	const char* ps =
		R"CODE( #version 330 core
				out vec4 FragColor;

				uniform vec4 color;
				in vec3 vert;

				float checkerboard(in vec3 uv)
				{
					vec3 pos = round(uv+ 0.0001) ;
					return mod(pos.x + mod(pos.y + mod(pos.z, 2.0), 2.0), 2.0);
				}

				void main()
				{
					float p = checkerboard(vert * 7);
					FragColor =  vec4(p + 0.4, p + 0.4, p  + 0.4, 1.0) * color;
				})CODE";

	ShaderProgram program(vs,ps);

	return program.ID;
}

*/