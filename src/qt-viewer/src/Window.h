#pragma once
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

#include "App.h"

class Window : public QMainWindow
{
	Q_OBJECT

private slots:
	void Import();

public:
	Window();
	~Window();

	App *app;

	// winodw components..
	QMenuBar *menuBar;
	QMenu *menuFile;
	QToolBar *V_toolbar;
	QByteArray filenamepath;
};