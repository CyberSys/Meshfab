#pragma once
#include <map>
#include <string>
#include <glm/glm.hpp>

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

	void colored_material(glm::mat4 mvp, glm::vec4 color);

	void framerender_material(unsigned int frametexture);

	std::map<std::string, unsigned int> programs;
};