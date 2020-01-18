#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>

using namespace std;

class Application
{
public:
	Application();

	~Application();

	void run();

	void resize();

private:
	GLFWwindow* window;
	int window_width;
	int window_height;
};