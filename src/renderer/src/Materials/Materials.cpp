#include "Materials.h"
#include "Private/ShaderProgram.h"
#include "Private/DefaultMaterial.h"
#include "Private/ColoredMaterial.h"
#include "Private/PhongMaterial.h"
#include "Private/CheckboardMaterial.h"
#include "Private/FramerenderMaterial.h"

Materials::Materials()
{
}

Materials::~Materials()
{
}

void Materials::init()
{
	//add default shader
	{
		DefaultMaterial material;
		int id = material.Create();
		programs.insert(std::pair<std::string, unsigned int>("default", id));
	}

	//add checkboard shader
	{
		CheckboardMaterial material;
		int id = material.Create();
		programs.insert(std::pair<std::string, unsigned int>("checkboard", id));
	}

	//add colored shader
	{
		ColoredMaterial material;
		int id = material.Create();
		programs.insert(std::pair<std::string, unsigned int>("colored", id));
	}

	//add phong shader
	{
		PhongMaterial material;
		int id = material.Create();
		programs.insert(std::pair<std::string, unsigned int>("phong", id));
	}

	//add framebuffer renderer material
	{
		FramerenderMaterial material;
		int id = material.Create();
		programs.insert(std::pair<std::string, unsigned int>("framerender", id));
	}

	//add diffuse shader
	
	//and so on..
}

void Materials::default_material(glm::mat4 mvp)
{
	//use colored shader and send data to gpu
	ShaderProgram program;
	program.ID = programs["default"];
	program.use();
	program.setMat4("mvp", mvp);
}

void Materials::checkboard_material(glm::mat4 mvp)
{
	//use checkboard shader and send data to gpu
	ShaderProgram program;
	program.ID = programs["checkboard"];
	program.use();
	program.setMat4("mvp", mvp);
}

void Materials::colored_material(glm::mat4 mvp, glm::vec4 color)
{
	//use colored shader and send data to gpu
	ShaderProgram program;
	program.ID = programs["colored"];
	program.use();
	program.setMat4("mvp", mvp);
	program.setVec4("objcolor", color);
}

void Materials::phong_material(glm::mat4 mvp, glm::mat4 model_mat, glm::vec3 light_dir, glm::vec3 light_color)
{
	//use phong shader and send data to gpu
	ShaderProgram program;
	program.ID = programs["phong"];
	program.use();
	program.setMat4("mvp", mvp);
	program.setMat4("model", model_mat);
	program.setVec3("light_dir", light_dir);
	program.setVec3("light_color", light_color);
}

void Materials::framerender_material(unsigned int frametexture)
{
	ShaderProgram program;
	program.ID = programs["framerender"];
	program.use();
	glBindTexture(GL_TEXTURE_2D, frametexture);
}
