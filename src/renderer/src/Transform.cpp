#include "Transform.h"

Transform::Transform() :
	position(glm::vec3(0)),
	rotation(glm::vec3(0)),
	scale(glm::vec3(1)),
	matrix(glm::mat4(1))
{
}

Transform::~Transform() {}
