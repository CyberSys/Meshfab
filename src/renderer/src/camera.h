#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/transform.hpp>
#include <vector>

// Default camera values
const float ZOOM = 45.0f;

// An abstract camera class that processes input 
//and calculates the corresponding Euler Angles,
//Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;

	// Camera options
	float Zoom;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	// Returns the projection matrix calculated using prespective Matrix
	glm::mat4 GetProjectionMatrix(float aspectratio);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

	void initArc(int windowwidth, int windowheight);

	bool mouseLeftDown = false;
	float mouseX = 0, mouseY = 0;
	float prevX, prevY = 0;
	float cameraDistance;
	float radius;

	glm::quat prevquat = glm::identity<glm::quat>();
	glm::quat quat= glm::identity<glm::quat>();

	glm::mat4 rotationmat = glm::mat4(1.0f);

	void Arcball_rotate();

	//    
	int windowWidth;
	int windowHeight;
	float rollSpeed;
	float angle;
	glm::vec3 prevPos;
	glm::vec3 currPos;
	glm::vec3 camAxis;
	bool xAxis;
	bool yAxis;

	//      
	glm::vec3 get_arcball_vector(int x, int y) ;
};