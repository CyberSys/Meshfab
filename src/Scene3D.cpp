#include "Scene3D.h"
#include <glew.h>

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
	materials.init();

	frame.Create(frame_width, frame_height);

	fb_renderer.init();

	obj = new SceneObject();

	//enable flags
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void Scene3D::Render()
{
	//use frame buffer to render to it
	frame.begin();

	//always clear to zeros ..
	glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render all you want here 
	view = camera.GetViewMatrix();
	projection = camera.GetProjectionMatrix( frame.AspectRatio());

	//select material you want ...
	materials.colored_material(obj->TransformMatrix(projection * view),glm::vec4(1,0,0,1));
	glBindVertexArray(obj->buffers.vao);
	glDrawArrays(GL_TRIANGLES, 0, obj->buffers.num_triangles);

	frame.end();

	materials.framerender_material(frame.ColorTexture_Get());
	fb_renderer.render();
}

void Scene3D::resize(int newwidth, int newheight)
{
	frame.resize(newwidth,newheight);
}
