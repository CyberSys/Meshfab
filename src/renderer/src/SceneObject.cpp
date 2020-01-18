#include "SceneObject.h"
#include "GeoShapes/Shape3D.h"

#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(ObjectType otype, MaterialType mtype) :
	name("object"),
	color(glm::vec4(1))
{
	type_object = otype;

	switch (otype)
	{
	case Empty:
		break;
	case Cube:
		buffers = Shape3D::Create_Cube();
		type_material = mtype;
		break;
	default:
		break;
	}
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
