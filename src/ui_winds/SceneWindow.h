#pragma once
#include <glfw3.h>

class SceneWindow
{
public:
	SceneWindow();

	~SceneWindow();

	void render(void* render_texture);

	int width_get();
	int hieght_get();

private:
	int m_width;
	int m_height;

	//framebuffer to draw on...
};