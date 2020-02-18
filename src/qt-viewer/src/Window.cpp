#include "Window.h"
#include "Actions.h"

#include <QFileDialog>

Window::Window()
{
	// window menubar
	menuBar = new QMenuBar;
	//menuFile = menuBar->addMenu(tr("&File"));
	setMenuBar(menuBar);

	{ // side toolbar
		V_toolbar = new QToolBar;
		V_toolbar->setIconSize(QSize(50,50));
		addToolBar(Qt::LeftToolBarArea, V_toolbar);
		V_toolbar->setMovable(false);
		QPixmap import_icon("resources/import.png");
		QAction *import_action = V_toolbar->addAction(QIcon(import_icon), "Import");
		connect(import_action, &QAction::triggered, this, &Window::Import);
		QPixmap select_icon("resources/select.png");
		QAction *select_action = V_toolbar->addAction(QIcon(select_icon), "Select");
		//connect(import_action, &QAction::triggered, this, &Window::Import);
		QPixmap shaders_icon("resources/shader.png");
		QAction *shaders_action = V_toolbar->addAction(QIcon(shaders_icon), "Shaders");
		//connect(import_action, &QAction::triggered, this, &Window::Import);
		QPixmap wireframe_icon("resources/wireframe.png");
		QAction *wireframe_action = V_toolbar->addAction(QIcon(wireframe_icon), "Wireframe");
		connect(wireframe_action, &QAction::triggered, this, &Window::Active_Wireframe);
		QPixmap bbox_icon("resources/boundingbox.png");
		QAction *bbox_action = V_toolbar->addAction(QIcon(bbox_icon), "Bounding Box");
		connect(bbox_action, &QAction::triggered, this, &Window::Active_BoundingBox);
	}

	app = new App();
	setCentralWidget(app);
}

Window::~Window()
{
	delete app;
	delete menuBar;
	delete menuFile;
	delete V_toolbar;
}

void Window::Import()
{
	//open file dialog and get path of this model
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Model File"), "", tr(""));
	filenamepath = fileName.toLocal8Bit();
	char* file = filenamepath.data();

	if(fileName.count() > 0) Actions::Add_Model(file);
}

void Window::Active_BoundingBox()
{
	Actions::Add_BBox();
}

void Window::Active_Wireframe()
{
	Actions::Active_Wireframe();
}