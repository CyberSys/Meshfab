#pragma once
#include <glfw3.h>

class Input
{
public:
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);

	static void cursor_callback(GLFWwindow* window, double xpos, double ypos);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};