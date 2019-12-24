#include "Input.h"
#include "camera.h"

Camera* Input::Scene_Camera = nullptr;


bool Input::firstMouse = false;
float Input::lastX = 800.0f / 2.0f;
float Input::lastY = 600.0f / 2.0f;

void Input::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{


	if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
	{
		if (firstMouse)
		{
			lastX = (float)xpos;
			lastY = (float)ypos;
			firstMouse = false;
		}

		float xoffset = (float)xpos - lastX;
		float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top
		lastX = (float)xpos;
		lastY = (float)ypos;

		Scene_Camera->ProcessMouseMovement((float)xpos, (float)ypos);
	}
		
}

void Input::scroll_callback(GLFWwindow * window, double, double yoffset)
{
	Scene_Camera->ProcessMouseScroll((float)yoffset);
}
