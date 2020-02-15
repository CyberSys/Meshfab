#pragma once
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

class Window : public QMainWindow
{
	Q_OBJECT

private slots:
	void Import();

public:
	Window();

	// winodw components..
	QMenuBar *menuBar;
	QMenu *menuFile;
	QToolBar *V_toolbar;
};