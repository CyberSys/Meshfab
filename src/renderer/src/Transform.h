#pragma once
#include <glm.hpp>

class Transform
{
public:
	Transform();

	~Transform();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 matrix;
	glm::mat4 vp_matrix;
};