#include "UI.h"
#include "Actions.h"

#include <iostream>

#include <Model.h>

UI::UI(){}

UI::~UI(){}

void UI::init(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void UI::Begin_UIFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::Draw_SelectionModesWindow()
{
	ImGui::Begin("Selection");
	
	if(ImGui::ImageButton(NULL,ImVec2(25,25)))
	{
		
	}
	ImGui::SameLine();
	if(ImGui::ImageButton(NULL,ImVec2(25,25)))
	{
		
	}
	ImGui::SameLine();
	if(ImGui::ImageButton(NULL,ImVec2(25,25)))
	{
		
	}
	ImGui::End();
}

void UI::Draw_PrimativesWindow()
{
	ImGui::Begin("k");
	
	if (ImGui::ImageButton(NULL, ImVec2(25, 25)))
	{
		Actions::Add_Model();
	}

	ImGui::End();

}

void UI::Draw_StaticsWindow()
{
	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Statics");               // Display some text (you can use a format strings too)

	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void UI::Draw_FileDialogWindow()
{
	//if button pressed do this
	//ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp\0.h\0.hpp\0\0", ".");

	if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk == true)
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			// action
		}
		// close
		ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
	}
}

void UI::End_UIFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
