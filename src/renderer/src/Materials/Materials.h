#pragma once
#include <map>
#include <string>
#include <glm.hpp>

/*
* this class contains all shader programs
* to shade any geomtrey with specific shader
*/

class Materials
{
public:
	Materials();

	~Materials();

	void init();

	void default_material(glm::mat4 mvp);

	void checkboard_material(glm::mat4 mvp);

	void colored_material(glm::mat4 mvp, glm::vec4 color);

	void phong_material(glm::mat4 mvp, glm::mat4 model_mat, glm::vec3 light_dir, glm::vec3 light_color);

	void framerender_material(unsigned int frametexture);

	std::map<std::string, unsigned int> programs;
};