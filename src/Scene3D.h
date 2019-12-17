#pragma once
#include "FrameBuffer.h"
#include "Framerenderer.h"
#include "camera.h"
#include "SceneObject.h"
#include "Materials/Materials.h"


class Scene3D
{
public:
	Scene3D();

	~Scene3D();

	void init(int frame_width,int frame_height);

	void Render();

	void resize(int newwidth, int newheight);

private:
	Frambuffer frame;
	Framerenderer fb_renderer;
	Camera camera;
	Materials materials;


	std::vector<SceneObject> objects;
};