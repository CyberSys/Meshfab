#include "SceneObject.h"
#include "GeoShapes/Shape3D.h"

#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject()
{
	buffers = Shape3D::Create_Cube();
}

SceneObject::~SceneObject() {}

glm::mat4 SceneObject::TransformMatrix(glm::mat4 vp)
{
	transformation.matrix = glm::translate(transformation.matrix,transformation.position);

	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transformation.matrix = glm::scale(transformation.matrix,transformation.scale);

	return vp * transformation.matrix;
}
