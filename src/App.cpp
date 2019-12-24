#include "App.h"
#include "Input.h"
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
	glfwSetCursorPosCallback(window, Input::mouse_callback);
	glfwSetScrollCallback(window, Input::scroll_callback);

	if (glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	scene3d.init(window_width,window_height);
}

Application::~Application()
{
	glfwTerminate();
}

void Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		//check for window resizing..
		resize();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene3d.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::resize()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	//if resized ..
	if (width != window_width || height != window_height)
	{
		window_width = width;
		window_height = height;

		glViewport(0, 0, width, height);
		scene3d.resize(width, height);
	}
}