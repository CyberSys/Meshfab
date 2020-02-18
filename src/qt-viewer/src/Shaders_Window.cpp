#include "Shaders_Window.h"

Shader_Window::Shader_Window(QWidget * parent)
	: widget_size(0,0,200,600)
{
	m_widget = new QWidget(parent);
	m_widget->setStyleSheet("background-color: lightgray");
	m_widget->setGeometry(widget_size);
	m_widget->setFixedSize(widget_size.size());
}

Shader_Window::~Shader_Window()
{
	delete m_widget;
}

void Shader_Window::SetPosition(int x, int y)
{
	widget_size.setX(x);
	widget_size.setY(y);
	m_widget->setGeometry(widget_size);
}

void Shader_Window::SetSize(int w, int h)
{
	widget_size.setSize(QSize(w,h));
	m_widget->setFixedSize(widget_size.size());
}

void Shader_Window::show()
{
	m_widget->show();
}
