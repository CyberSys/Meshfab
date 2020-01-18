#pragma once
#include "Framerenderer.h"
#include "SceneObject.h"
#include "Materials/Materials.h"

#include <vector>
using namespace std;

class Renderer
{
public:
	Renderer();

	~Renderer();

	void init();

	void flush(unsigned int finalframe);

	void filled_draw(SceneObject* obj);

	void wireframe_draw(SceneObject* obj);

	Materials materials;
	Framerenderer framerenderer;
};