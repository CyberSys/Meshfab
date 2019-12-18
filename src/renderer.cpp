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

void Renderer::draw(SceneObject* obj)
{
	selectmaterial(obj, materials);
	
	glBindVertexArray(obj->buffers.vao);
	glDrawArrays(GL_TRIANGLES, 0, obj->buffers.num_triangles);
}
