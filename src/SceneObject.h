#pragma once
#include "GeoShapes/private/GPUBufferID.h"
#include <string>


class SceneObject
{
public:
	SceneObject();

	~SceneObject();

	GPUBufferID buffers;
	std::string name;
	std::string materialName;
};