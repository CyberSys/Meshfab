#pragma once

#include <glfw3.h>

class MainWindow
{
public:

	//create window with size or maxmized
	MainWindow(const char* title);

	~MainWindow();

	int GetWindowWidth();

	int GetWindowHeight();

	bool IsWindowClosed();

	void WindowBeginFrame();

	void WindowEndFrame();

	GLFWwindow* GetWindowPtr();

private:
	int m_width;
	int m_height;

	GLFWwindow* m_window;

	void InputListener();
};