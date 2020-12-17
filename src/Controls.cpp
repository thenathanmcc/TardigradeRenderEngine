/*
 * Controls class implementation
 * @author Nathan McCulloch
 */

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"

using namespace glm;


#include "Controls.hpp"


Controls::Controls(Camera* camera) {
	m_camera = camera;
	m_movementSpeed = 3.0f;
	m_rotateSpeed = 0.005f;

	m_pitchAngle = 0.0f;
	m_yawAngle = 3.14f;

	m_mouseFocus = true;

	m_screenshotCount = 0;
}



void Controls::checkUserInputs(GLFWwindow* window) {
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	glfwGetWindowSize(window, &m_windowWidth, &m_windowHeight);

	// Get mouse coordinates
	if (m_mouseFocus) {
		glfwGetCursorPos(window, &m_xcoord, &m_ycoord);
		// Reset mouse position for next frame
		glfwSetCursorPos(window, m_windowWidth/2, m_windowHeight/2);
	}

	// Compute new orientation
	m_pitchAngle += m_rotateSpeed * float(m_windowHeight/2 - m_ycoord);
	m_yawAngle   += m_rotateSpeed * float(m_windowWidth/2 - m_xcoord);


	// Convert Spherical ccoordinates to cartesian coordinates
	glm::vec3 direction (
		cos(m_pitchAngle) * sin(m_yawAngle),
		sin(m_pitchAngle),
		cos(m_pitchAngle) * cos(m_yawAngle)
	);

	glm::vec3 right = glm::vec3 (
		sin(m_yawAngle - 3.14f/2.0f),
		0,
		cos(m_yawAngle - 3.14f/2.0f)
	);

	glm::vec3 position = m_camera->getPosition();

	glm::vec3 up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * m_movementSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * m_movementSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * m_movementSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * m_movementSpeed;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		m_mouseFocus = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//m_mouseFocus = true;
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		std::cout << "Screenshot" << std::endl;
		takeScreenshot(window);
	}


	m_camera->setCameraTarget(position, position + direction, up);
	lastTime = currentTime;
}

void Controls::setCameraMovementSpeed(float speed) {
	m_movementSpeed = speed;
}

void Controls::setCameraRotatingSpeed(float speed) {
	m_rotateSpeed = speed;
}

void Controls::takeScreenshot(GLFWwindow* window) {

	char *data = (char*) malloc((size_t) (m_windowWidth * m_windowHeight * 3)); // 3 components (R, G, B)

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, m_windowWidth, m_windowHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

    int saved = stbi_write_png("screenshot.png", m_windowWidth, m_windowHeight, 3, data, 0);

    free(data);

}