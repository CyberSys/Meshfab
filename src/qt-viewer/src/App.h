#pragma once
#include <glew.h>
#include <QOpenGLWidget>

#include "renderer.h"

class App : public QOpenGLWidget
{
	Q_OBJECT

public:
	App(QWidget *parent = nullptr);

	~App();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	//mouse events
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event);

	//keyboard events
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
private:
	Renderer renderer;
};