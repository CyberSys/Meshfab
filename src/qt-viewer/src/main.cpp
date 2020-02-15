#include <QApplication>
#include <QDesktopWidget>
#include "Window.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("Meshfab");
	QCoreApplication::setOrganizationName("sha3lan");
	Window w;
	w.resize(w.sizeHint());
	w.showMaximized();
	return a.exec();
}