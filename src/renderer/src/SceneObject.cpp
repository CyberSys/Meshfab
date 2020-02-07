#include "SceneObject.h"
#include "Shape3D.h"

#include <gtc/matrix_transform.hpp>

int SceneObject::obj_num = 0;


SceneObject::SceneObject(GeomtryInfo info) :
	name("object"+obj_num),
	color(glm::vec4(1)),
	type_material(MaterialType::Default)
{
	buffers = info;
	++obj_num;
}

SceneObject::~SceneObject() {}

glm::mat4 SceneObject::TransformMatrix()
{
	transformation.matrix = glm::translate(transformation.matrix,transformation.position);

	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformation.matrix = glm::rotate(transformation.matrix, glm::radians(transformation.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transformation.matrix = glm::scale(transformation.matrix,transformation.scale);

	return transformation.vp_matrix * transformation.matrix;
}

glm::mat4 SceneObject::ModelMatrix()
{
	return transformation.matrix;
}
