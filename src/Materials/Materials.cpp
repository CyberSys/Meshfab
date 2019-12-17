#include "Materials.h"
#include "Private/ShaderProgram.h"
#include "Private/ColoredMaterial.h"

Materials::Materials()
{
}

Materials::~Materials()
{
}

void Materials::init()
{
	//add colored shader
	ColoredMaterial material;
	int id = material.Create();
	programs.insert(std::pair<std::string, unsigned int>("colored", id));

	//add diffuse shader

	//and so on..
}

void Materials::colored_material(glm::mat4 mvp, glm::vec4 color)
{
	//use colored shader and send data to gpu
	ShaderProgram program;
	program.ID = programs["colored"];
	program.use();
	program.setMat4("mvp", mvp);
	program.setVec4("color", color);
}
