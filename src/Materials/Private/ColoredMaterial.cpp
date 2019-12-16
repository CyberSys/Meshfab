#include "ColoredMaterial.h"
#include "ShaderProgram.h"

ColoredMaterial::ColoredMaterial() {}

ColoredMaterial::~ColoredMaterial() {}

unsigned int ColoredMaterial::Create()
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

				uniform vec4 color;

				void main()
				{
					FragColor = color;
				})CODE";

	ShaderProgram program(vs,ps);

	return program.ID;
}
