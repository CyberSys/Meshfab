#pragma once
#include "GeoShapes/private/GeomtryInfo.h"
#include "Transform.h"
#include <string>

class SceneObject
{
public:
	SceneObject();

	~SceneObject();

	glm::mat4 TransformMatrix(glm::mat4 vp);

	Transform transformation;

	GeomtryInfo buffers;
	std::string name;
	std::string materialName;
};