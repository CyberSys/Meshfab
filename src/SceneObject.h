#pragma once
#include "GeoShapes/private/GPUBufferID.h"
#include "Transform.h"
#include <string>

class SceneObject
{
public:
	SceneObject();

	~SceneObject();

	Transform transformation;

	GPUBufferID buffers;
	std::string name;
	std::string materialName;
};