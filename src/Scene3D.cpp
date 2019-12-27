#include "Scene3D.h"
#include <glew.h>

#include "Input.h"

Scene3D::Scene3D() : 
	view(glm::mat4(1)),
	projection(glm::mat4(1))
{
}

Scene3D::~Scene3D()
{
}

void Scene3D::init(int frame_width, int frame_height)
{

	renderer.init();

	frame.Create(frame_width, frame_height);

	addobject(ObjectType::Cube,MaterialType::Default);

	camera.initArc(frame_width,frame_height);
	Input::Scene_Camera = (Camera*)&camera;

	//enable flags
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void Scene3D::Render()
{
	//use frame buffer to render to it
	frame.begin();

	//always clear to zeros ..
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render all you want here 
	view = camera.GetViewMatrix();
	projection = camera.GetProjectionMatrix( frame.AspectRatio());

	for (size_t i = 0 ; i < objects.size(); ++i)
	{
		objects[i]->transformation.vp_matrix = projection * view;
		renderer.draw(objects[i]);
	}

	frame.end();

	renderer.flush(frame.ColorTexture_Get());
}

void Scene3D::resize(int newwidth, int newheight)
{
	frame.resize(newwidth,newheight);
}

void Scene3D::addobject(ObjectType otype, MaterialType mtype)
{
	SceneObject* obj = new SceneObject(otype,mtype);
	objects.push_back(obj);
}