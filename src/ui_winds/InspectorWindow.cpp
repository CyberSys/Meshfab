#include "InspectorWindow.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/ImGuizmo.h"

#include <glm.hpp>

InspectorWindow::InspectorWindow() :
	m_width(400),
	m_height(400),
	m_translation(glm::vec3(0)),
	m_rotation(glm::vec3(0)),
	m_scale(glm::vec3(0))

{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::render(void* render_texture)
{
	bool show_window = true;
	ImVec4 curent_translation = ImVec4(m_translation.x, m_translation.y, m_translation.z, 1.00f);
	ImVec4 curent_rotation = ImVec4(m_rotation.x, m_rotation.y, m_rotation.z, 1.00f);
	ImVec4 curent_scale = ImVec4(m_scale.x, m_scale.y, m_scale.z, 1.00f);

	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		ImGui::Begin("Transform", &show_window, window_flags);     // Create a window 
		ImGui::InputFloat3("Translation", (float*)&curent_translation);
		ImGui::InputFloat3("Rotation", (float*)&curent_rotation);
		ImGui::InputFloat3("Scale", (float*)&curent_scale);
		ImGui::Separator();
		ImGui::End();
	}
}

int InspectorWindow::width_get()
{
	return m_width;
}

int InspectorWindow::hieght_get()
{
	return m_height;
}
