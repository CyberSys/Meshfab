#include <glew.h>


#include "MainWindow.h"

#include <iostream>

int main()
{
	MainWindow *mainwindow = new MainWindow("Hello Window");

	if (glewInit())
	{
		std::cout << "Failed to initialize glew" << std::endl;
		return -1;
	}


	// render loop
	// -----------
	while (!mainwindow->IsWindowClosed())
	{
		mainwindow->WindowBeginFrame();
	
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	

		mainwindow->WindowEndFrame();
	}

	return 0;
}