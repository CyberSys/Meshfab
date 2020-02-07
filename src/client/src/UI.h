#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui/imgui.h"
#include "imgui/ImGuiFileDialog.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


class UI
{
public:
	UI();

	~UI();

	void init(GLFWwindow* window);

	void Begin_UIFrame();

	void Draw_SelectionModesWindow();

	void Draw_PrimativesWindow();

	void Draw_StaticsWindow();

	void Draw_FileDialogWindow();

	void End_UIFrame();
};