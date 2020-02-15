#include "Window.h"

Window::Window()
{
	// window menubar
	menuBar = new QMenuBar;
	menuFile = menuBar->addMenu(tr("&File"));
	setMenuBar(menuBar);

	{ // side toolbar
		V_toolbar = new QToolBar;
		V_toolbar->setIconSize(QSize(50,50));
		addToolBar(Qt::LeftToolBarArea, V_toolbar);
		V_toolbar->setMovable(false);
		QPixmap import_icon("resources/import.png");
		QAction *import_action = V_toolbar->addAction(QIcon(import_icon), "Import");
		connect(import_action, &QAction::triggered, this, &Window::Import);
	}
}

void Window::Import()
{
}