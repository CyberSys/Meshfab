#include "renderer.h"

#include <glew.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::init()
{
	materials.init();

	framerenderer.init();
}

void Renderer::flush(unsigned int finalframe)
{
	materials.framerender_material(finalframe);
	framerenderer.render();
}

inline static void selectmaterial(SceneObject* obj, Materials& materials)
{
	switch (obj->type_material)
	{
	case MaterialType::Default:
		materials.colored_material(obj->TransformMatrix(), obj->color);
		break;
	case MaterialType::Diffuse:
		break;
	default:
		break;
	}
}

void Renderer::filled_draw(SceneObject* obj)
{
	selectmaterial(obj, materials);
	
	glBindVertexArray(obj->buffers.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->buffers.ibo);

	glDrawElements(GL_TRIANGLES, obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);
}

void Renderer::wireframe_draw(SceneObject* obj)
{
	selectmaterial(obj, materials);

	glBindVertexArray(obj->buffers.vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->buffers.ibo);

	//glDrawElements(GL_TRIANGLES, obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);

	glLineWidth(3);
	glm::vec4 tmp = obj->color;
	obj->color = glm::vec4(0, 0.3, 0.8, 0.5);
	selectmaterial(obj, materials);
	glDrawElements(GL_LINES, obj->buffers.num_indecies, GL_UNSIGNED_INT, 0);

	obj->color = tmp;
	glLineWidth(1);
}