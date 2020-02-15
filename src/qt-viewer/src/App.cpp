#include "App.h"

App::App(QWidget *parent) : QOpenGLWidget(parent)
{

}

App::~App()
{
}

void App::initializeGL()
{
}

void App::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,0.5,0.5,1);
}

void App::resizeGL(int width, int height)
{
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