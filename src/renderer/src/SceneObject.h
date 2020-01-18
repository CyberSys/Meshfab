#pragma once
#include "private/GeomtryInfo.h"
#include "Transform.h"
#include <string>

enum ObjectType
{
	Empty,
	Cube
};

enum MaterialType
{
	Default,
	Diffuse
};

class SceneObject
{
public:
	SceneObject(ObjectType otype, MaterialType mtype);

	~SceneObject();

	glm::mat4 TransformMatrix();

	Transform transformation;

	GeomtryInfo buffers;
	std::string name;
	glm::vec4 color;

	ObjectType type_object;
	MaterialType type_material;
};