#pragma once
#include "FrameBuffer.h"
#include "camera.h"
#include "SceneObject.h"
#include "renderer.h"

class Scene3D
{
public:
	Scene3D();

	~Scene3D();

	void init(int frame_width,int frame_height);

	void Render();

	void resize(int newwidth, int newheight);

	void addobject(ObjectType otype, MaterialType mtype);

private:
	Frambuffer frame;
	Camera camera;
	Renderer renderer;

	glm::mat4 view;
	glm::mat4 projection;

	std::vector<SceneObject*> objects;
};