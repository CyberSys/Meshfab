#include "Input.h"
#include "Actions.h"
#include <iostream>
using namespace std;

void Input::mouse_callback(GLFWwindow * window, int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	Actions::Input_MousePress(button,action,mods,x,y);
}

void Input::cursor_callback(GLFWwindow * window, double xpos, double ypos)
{
	Actions::Input_CursorMove(xpos, ypos);
}

void Input::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	Actions::Input_MouseWheel(xoffset, yoffset);
}
