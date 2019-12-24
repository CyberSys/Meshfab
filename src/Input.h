#pragma once
#include <glfw3.h>

class Camera;
class Input
{
public:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static Camera* Scene_Camera;

	static bool firstMouse;
	static float lastX;
	static float lastY;
};