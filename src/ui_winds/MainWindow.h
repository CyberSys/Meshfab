#pragma once
#include <glfw3.h>

#include "SceneWindow.h"
#include "InspectorWindow.h"

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

	SceneWindow* SceneWind_Get();

	InspectorWindow* InspWind_Get();

private:
	int m_width;
	int m_height;

	GLFWwindow* m_window;
	SceneWindow scene_wind;
	InspectorWindow inspector_wind;

	void InputListener();
	void setup_imgui();
	void render_imgui();
};