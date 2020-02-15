#include "FramerenderMaterial.h"
#include "ShaderProgram.h"

FramerenderMaterial::FramerenderMaterial() {}

FramerenderMaterial::~FramerenderMaterial() {}

unsigned int FramerenderMaterial::Create()
{
	const char* vs =
		R"CODE( #version 330 core
				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec2 uv;
				
				out vec2 TexCoords;
				
				void main()
				{
					TexCoords = uv;
					gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0);
				})CODE";

	const char* ps =
		R"CODE( #version 330 core
				out vec4 FragColor;
				
				in vec2 TexCoords;
				
				uniform sampler2D framebufferTexture;
				
				void main()
				{
					vec3 col = texture(framebufferTexture, TexCoords).rgb;
					FragColor = vec4(col, 1.0);
				})CODE";

	ShaderProgram program(vs, ps);

	return program.ID;
}
