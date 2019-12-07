#include "MainWindow.h"

#include <iostream>

MainWindow::MainWindow(const char * title)
{
	int x = glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


	m_window = glfwCreateWindow(1024, 720, title, NULL, NULL);

	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwGetWindowSize(m_window, &m_width, &m_height);
	glfwMakeContextCurrent(m_window);
}

MainWindow::~MainWindow()
{
	glfwTerminate();
}

int MainWindow::GetWindowWidth()
{
	return m_width;
}

int MainWindow::GetWindowHeight()
{
	return m_height;
}

bool MainWindow::IsWindowClosed()
{
	return glfwWindowShouldClose(m_window);
}

void MainWindow::WindowBeginFrame()
{
	InputListener();
}

void MainWindow::WindowEndFrame()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void MainWindow::InputListener()
{
	//here will process all inputs related to this app
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

}

GLFWwindow * MainWindow::GetWindowPtr()
{
	return nullptr;
}
