#pragma once
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

#include "App.h"
#include "Shaders_Window.h"

class Window : public QMainWindow
{
	Q_OBJECT

private slots:
	void Import();
	void Active_Shaders_Panel();
	void Active_BoundingBox();
	void Active_Wireframe();

public:
	Window();
	~Window();

	App *app;
	Shader_Window* shader_window;

	// winodw components..
	QMenuBar *menuBar;
	QMenu *menuFile;
	QToolBar *V_toolbar;
	QByteArray filenamepath;
};