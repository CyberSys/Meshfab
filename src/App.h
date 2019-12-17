#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

using namespace std;

#include "Scene3D.h"

class Application
{
public:
	Application();

	~Application();

	void run();

	void input();

	static void mouse_position(double xpos, double ypos);

	static void mouse_scroll(double xoffset, double yoffset);

	void resize();

private:
	GLFWwindow* window;
	int window_width;
	int window_height;

	Scene3D scene3d;

	void frameresize(int width, int height);
};