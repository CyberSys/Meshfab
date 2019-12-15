#pragma once
#include <glfw3.h>
#include <glm.hpp>

class InspectorWindow
{
public:
	InspectorWindow();

	~InspectorWindow();

	void render(void* render_texture);

	int width_get();
	int hieght_get();

private:
	int m_width;
	int m_height;

	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};