#pragma once
#include "private/GeomtryInfo.h"
#include "Transform.h"
#include <string>

enum MaterialType
{
	Default,
	Colored,
	Phong,
	Checkboard,
	Diffuse
};

enum DrawMode
{
	KIND_FILLED,
	KIND_WIREFRAME
};

class SceneObject
{
public:
	SceneObject(GeomtryInfo info);

	~SceneObject();

	glm::mat4 TransformMatrix();

	glm::mat4 ModelMatrix();

	glm::vec4 color;
	std::string name;
	GeomtryInfo buffers;
	Transform transformation;
	MaterialType type_material;

	static int obj_num;
};