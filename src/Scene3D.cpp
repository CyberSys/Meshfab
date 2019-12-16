#include "Scene3D.h"
#include <glew.h>

Scene3D::Scene3D()
{
}

Scene3D::~Scene3D()
{
}

#include "GeoShapes\Shape3D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Shape3D sh;
unsigned int vao;

void Scene3D::init(int frame_width, int frame_height)
{
	frame.Create(frame_width, frame_height);

	//init geomtrey
	vao = sh.Create_Cube().vao;
}

void* Scene3D::Render()
{
	//use frame buffer to render to it
	frame.Use();

	//enable flags
	glEnable(GL_DEPTH_TEST);

	//always clear to zeros ..
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render all you want here 
	glm::mat4 model = glm::mat4(1);
	model = glm::rotate(model,10.0f,glm::vec3(1,1,0));
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), frame.AspectRatio(), 0.1f, 1000.0f);
	glm::mat4 mvp = projection * view * model;

	//select material you want ...
	materials.colored_material(mvp,glm::vec4(1,0,0,1));

	//select geom you want and draw it
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//then return final image..
	frame.Use_Prevframe();
	return (void*)frame.ColorTexture_Get();
}
