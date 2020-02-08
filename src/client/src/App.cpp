#include "App.h"
#include "Input.h"
#include "Actions.h"


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
	glfwSetCursorPosCallback(window, Input::cursor_callback);
	glfwSetMouseButtonCallback(window, Input::mouse_callback);
	glfwSetScrollCallback(window, Input::scroll_callback);

	if (glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	//init imgui module..
	APPUI.init(window);

	//enable flags
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

Application::~Application()
{
	//clear all scene objs
	Scene::Clear();

	//shutdown glfw
	glfwTerminate();
}

void Application::run()
{
	renderer.init(window_width, window_height);

	//add some features to my viewer here
	Actions::Add_BBox();

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		//Action Excution befor render frame..
		Actions::Excute();

		//check for window resizing..
		resize();

		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//renderer goes here..
		{
			//begin new frame to render on it
			renderer.frame.begin();

			//draw all scene objects
			renderer.Draw_sceneobjs(DrawMode::KIND_TRIANGLE);

			//draw grid as feature in our viewer
			renderer.Draw_object(Scene::viewer_grid, DrawMode::KIND_LINES);

			//end the frame rendering and flush.
			renderer.frame.end();
			renderer.flush(renderer.frame.ColorTexture_Get());
		}

		//rendering ui ..
		APPUI.Begin_UIFrame();
		APPUI.Draw_PrimativesWindow();
		APPUI.End_UIFrame();

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

		//resize renderer frame goes here..
		renderer.resize(width, height);
	}
}