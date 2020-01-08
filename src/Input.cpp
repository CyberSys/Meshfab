#include "Input.h"
#include "camera.h"
#include <iostream>
using namespace std;

Camera* Input::Scene_Camera = nullptr;


bool Input::firstMouse = true;
float Input::lastX = 800.0f / 2.0f;
float Input::lastY = 600.0f / 2.0f;

void Input::mouse_callback(GLFWwindow * window, int button, int action, int mods)
{		
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Scene_Camera->mouseLeftDown = true;

		// remember mouse coords and quaternion before rotation
		Scene_Camera->prevX = (float)x;
		Scene_Camera->prevY = (float)y;

		Scene_Camera->prevquat = Scene_Camera->quat;
		Scene_Camera->windowWidth = width;
		Scene_Camera->windowHeight = height;
	}
	else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		Scene_Camera->mouseLeftDown = false;
	}
}

void Input::cursor_callback(GLFWwindow * window, double xpos, double ypos)
{
	if(Scene_Camera->mouseLeftDown)
	{
		Scene_Camera->mouseX = (float)xpos;
		Scene_Camera->mouseY = (float)ypos;
		Scene_Camera->Arcball_rotate();
	}

}

void Input::scroll_callback(GLFWwindow * window, double, double yoffset)
{
	Scene_Camera->ProcessMouseScroll((float)yoffset);
}
