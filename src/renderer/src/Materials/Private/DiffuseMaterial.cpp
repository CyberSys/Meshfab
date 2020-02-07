#include "DiffuseMaterial.h"
#include "ShaderProgram.h"

DiffuseMaterial::DiffuseMaterial() {}

DiffuseMaterial::~DiffuseMaterial() {}

unsigned int DiffuseMaterial::Create()
{
	const char* vs = 
		R"CODE( #version 330 core
				layout (location = 0) in vec3 vertex;
				layout (location = 1) in vec3 normal;
				layout (location = 2) in vec2 uvs;

				uniform mat4 mvp;
				uniform mat4 model;
				uniform vec3 light_dir;
				uniform vec3 light_color;

				out vec3 v_color;
				out vec4 v_pos;
				out vec2 TexCoord;
				
				void main()
				{
					gl_Position = mvp * vec4(vertex, 1.0);
				
					vec3 world_pos = (model * vec4(vertex, 1.0)).xyz;
					vec3 _normal = normalize(mat3(transpose(inverse(model))) * normal);
				
					//ambient
					float ambient_factor = 0.1;
					vec3 ambient_color = ambient_factor * light_color;
				
					//diffuse
					vec3 dir = normalize(light_dir);
					float diffuse_factor = max(dot(_normal, dir), 0.0);
					vec3 diffuse_color = diffuse_factor * light_color;
				
					v_color = (ambient_color + diffuse_color) * vec3(0.8,0.8,0.8);
					v_pos =  model * vec4(vertex, 1.0);
					TexCoord = vec2(uvs.x, uvs.y);
				}


)CODE";

	const char* ps = 
		R"CODE( #version 330 core
				in vec3 v_color;
				in vec4 v_pos;
				
				out vec4 outColor;
				in vec2 TexCoord;
				
				uniform sampler2D diffuse_texture;
				void main()
				{
					outColor = vec4(v_color, 1.0f) * texture(diffuse_texture, TexCoord);
				})CODE";

	ShaderProgram program(vs,ps);

	return program.ID;
}