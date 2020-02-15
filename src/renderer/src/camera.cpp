#include "camera.h"
#include <iostream>
using namespace std;

Camera::Camera(glm::vec3 position, glm::vec3 up) :
	Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	Zoom(ZOOM),
	Up(up)
{
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectratio)
{
	return glm::perspective(glm::radians(Zoom), aspectratio, 0.1f, 1000.0f);
}

void Camera::initArc(int windowwidth, int windowheight)
{
	if (windowwidth > windowheight)
		radius = (float)windowheight * 0.5f;
	else
		radius = (float)windowwidth * 0.5f;

	cameraDistance = radius * 0.1f;
	Position = glm::vec3(0, 0, -15);

	this->windowWidth = windowwidth;
	this->windowHeight = windowheight;
	this->rollSpeed = 0.05f;
	this->angle = 0.0f;
	this->camAxis = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::Arcball_rotate()
{
	if (mouseX != prevX || mouseY != prevY) {

		glm::vec3 va = get_arcball_vector((int)prevX, (int)prevY);
		glm::vec3 vb = get_arcball_vector((int)mouseX, (int)mouseY);
		float angle = acos(glm::min(1.0f, glm::dot(va, vb)));
		glm::vec3 axis_in_camera_coord = glm::cross(va, vb);

		axis_in_camera_coord = glm::vec4(axis_in_camera_coord, 1.0f) * GetViewMatrix();
		glm::mat4 tr = glm::rotate(glm::degrees(angle) * rollSpeed, axis_in_camera_coord);

		tr = glm::inverse(tr);
		Position = tr * glm::vec4(Position, 1);
		Up = tr * glm::vec4(Up, 1);
		Front = tr * glm::vec4(Front, 1);

		prevX = mouseX;
		prevY = mouseY;
	}
}

glm::vec3 Camera::get_arcball_vector(int x, int y)
{
	glm::vec3 P = glm::vec3(1.0*x / this->windowWidth * 2 - 1.0,
		1.0*y / this->windowHeight * 2 - 1.0,0);

	P.y = -P.y;
	float OP_squared = P.x * P.x + P.y * P.y;
	if (OP_squared <= 1 * 1)
		P.z = sqrt(1 * 1 - OP_squared);  // Pythagoras
	else
		P = glm::normalize(P);  // nearest point

	return P;
}

