#include "Controls.h"
#include "glHeader.h"
#include "defs.h"

using namespace glm;

Controls::Controls(GLFWwindow* w)
{
	window = w;

	// Set them to identity for right now
	projectionMatrix = mat4(1.0f);
	viewMatrix       = mat4(1.0f);

	FOV = 45;

	hAngle = 0.0f;
	vAngle = 0.0f;

	speed = 6.0f;
	mouseSpeed = 0.01f;

	position = glm::vec3( 10, -10, 3 );

	wireframeEnabled = false;

}

Controls::~Controls()
{

}

mat4 Controls::getProjectionMatrix()
{
	return projectionMatrix;
}

mat4 Controls::getViewMatrix()
{
	return viewMatrix;
}

void Controls::computeMatrices()
{
	// Get the time when this function is called,
	//  this should only be called once due to the 
	//  static typing
	static double prevFrameTime = glfwGetTime();
	double currentTime = glfwGetTime();

	// Time difference
	float deltaTime = float(currentTime - prevFrameTime);

	// Get mouse position
	double mouseX;
	double mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);


	// Set the mouse position back to center so that
	//  the cursor doesnt go too far off screen
	// TODO: Make this dynamic so the screen can be resized
	glfwSetCursorPos(window, WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);


	// Compute Orientation

	// Explanation: This works by taking the amount of distance 
	//  the user moved the mouse times the speed of the change
	//  that we defined above (mouseSpeed). The variable mouseSpeed
	//  we defined can be changed to suit the user
	hAngle += mouseSpeed * (float)(WINDOW_WIDTH/2.0f - mouseX) * -1.0f;
	vAngle += mouseSpeed * (float)(WINDOW_HEIGHT/2.0f - mouseY);


	// Compute the direction of the camera
	//  Spherical coordinates to Cartesian coordinates conversion
	vec3 direction(
		cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle)
		);

	vec3 right(
		sin(hAngle - PI/2.0f),
		0,
		cos(hAngle - PI/2.0f)
		);

	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
	    position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
	    position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
	    position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
	    position -= right * deltaTime * speed;
	}

	// Zoom, I added this - Austin :P
	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
	{
		if (FOV <= 60)
		{
			FOV++;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
	{
		if (FOV >= 30)
		{
			FOV--;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		position -= vec3(0.0f, -0.1f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position -= vec3(0.0f, 0.1f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		wireframeEnabled = !wireframeEnabled;

		if (wireframeEnabled)
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
		else
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}
	}

	projectionMatrix = glm::perspective(glm::radians(FOV), ASPECT_RATIO, 0.1f, 100.0f);

	viewMatrix = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	prevFrameTime = currentTime;
}