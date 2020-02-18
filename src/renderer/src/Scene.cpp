#include "Scene.h"

std::vector<SceneObject*> Scene::scene_objs;
SceneObject* Scene::viewer_grid = nullptr;
SceneObject* Scene::viewer_bbox = nullptr;
DrawMode Scene::draw_mode = DrawMode::KIND_FILLED;

void Scene::Add(SceneObject * obj)
{
	scene_objs.push_back(obj);
}

void Scene::Clear()
{
	delete viewer_grid;
	delete viewer_bbox;
	
	for (auto obj : scene_objs)
		delete obj;
}
