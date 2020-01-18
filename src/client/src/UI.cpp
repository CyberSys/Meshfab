#include "UI.h"
#include <iostream>

UI::UI()
{
}

UI::~UI()
{
}

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

void UI::Draw_PrimativesWindow()
{
	ImGui::Begin("Primatives");
	
	if(ImGui::ImageButton(NULL,ImVec2(50,50)))
	{
		
	}
	ImGui::SameLine();
	if(ImGui::ImageButton(NULL,ImVec2(50,50)))
	{
		
	}

	if(ImGui::ImageButton(NULL,ImVec2(50,50)))
	{
		
	}
	ImGui::SameLine();
	if(ImGui::ImageButton(NULL,ImVec2(50,50)))
	{
		
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

void UI::End_UIFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
