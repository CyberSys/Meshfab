#pragma once
#include "SceneObject.h"
#include <vector>

class Scene
{
public:
	static void Add(SceneObject* obj);
	static void Clear();

	static std::vector<SceneObject*> scene_objs;

	static SceneObject* viewer_grid;
	static SceneObject* viewer_bbox;
};