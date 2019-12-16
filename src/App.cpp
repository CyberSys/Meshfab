#include "App.h"

void resize_callback(GLFWwindow* window, int width, int height)
{
	Application::resize(width,height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Application::mouse_position(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application::mouse_scroll(xoffset,yoffset);
}

////////////////////////////////////////////////////
Application::Application() :
	window_width(800),
	window_height(600)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(window_width, window_height, "Viewer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}
}

Application::~Application()
{
	glfwTerminate();
}

void Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.4f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::input()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Application::mouse_position(double xpos, double ypos)
{

}

void Application::mouse_scroll(double xoffset, double yoffset)
{
}

void Application::resize(int width, int height)
{
	glViewport(0, 0, width, height);
}