#include "App.h"
#include "Actions.h"

#include <iostream>

App::App(QWidget *parent) : QOpenGLWidget(parent)
{

}

App::~App()
{
}

void App::initializeGL()
{
	if (glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	//enable flags
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	renderer.init(100, 100);

	//add some features to my viewer here
	Actions::Add_BBox();
}

void App::paintGL()
{
	//Action Excution befor render frame..
	Actions::Excute();

	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//renderer goes here..
	{
		//begin new frame to render on it
		renderer.frame.begin();

		//draw all scene objects
		renderer.Draw_sceneobjs(DrawMode::KIND_TRIANGLE);

		//end the frame rendering and flush.
		renderer.frame.end();
		renderer.flush(renderer.frame.ColorTexture_Get());
	}
}

void App::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	//resize renderer frame goes here..
	renderer.resize(width, height);
}

void App::mousePressEvent(QMouseEvent * event)
{
}

void App::mouseReleaseEvent(QMouseEvent * event)
{
}

void App::mouseMoveEvent(QMouseEvent * event)
{
}

void App::wheelEvent(QWheelEvent * event)
{
}

void App::keyPressEvent(QKeyEvent * event)
{
}

void App::keyReleaseEvent(QKeyEvent * event)
{
}