#pragma once
#include <qwidget.h>

class Shader_Window
{
public:
	Shader_Window(QWidget* parent);
	~Shader_Window();

	void SetPosition(int x, int y);
	void SetSize(int w, int h);
	void show();

private:
	QWidget* m_widget;
	QRect widget_size;
};