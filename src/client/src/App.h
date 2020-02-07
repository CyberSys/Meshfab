#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

#include "UI.h"

//renderer module
#include "Scene.h"
#include "renderer.h"

using namespace std;

class Application
{
public:
	Application();

	~Application();

	void run();

	void resize();

private:
	UI APPUI;
	GLFWwindow* window;
	int window_width;
	int window_height;

	Renderer renderer;
};