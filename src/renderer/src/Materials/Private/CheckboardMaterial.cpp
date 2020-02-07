#include "CheckboardMaterial.h"
#include "ShaderProgram.h"

CheckboardMaterial::CheckboardMaterial() {}

CheckboardMaterial::~CheckboardMaterial() {}

////***********************
//// checkhoard shader ****
////***********************

unsigned int CheckboardMaterial::Create()
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

				in vec3 vert;

				float checkerboard(in vec3 uv)
				{
					vec3 pos = round(uv+ 0.0001) ;
					return mod(pos.x + mod(pos.y + mod(pos.z, 2.0), 2.0), 2.0);
				}

				void main()
				{
					vec4 color = vec4(1.0,1.0,1.0,0.8);
					float p = checkerboard(vert);
					FragColor =  vec4(p + 0.4, p + 0.4, p  + 0.6, 1.0) * color;
				})CODE";

	ShaderProgram program(vs,ps);

	return program.ID;
}