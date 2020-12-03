/**
 * Camera class implementation
 * @author Nathan McCulloch
 */


#include "Camera.hpp"


Camera::Camera() {
	m_position = glm::vec3(0, 0, -3);
	m_target = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
	m_foV = 40.0f;
	m_projectionMatrix = glm::perspective(m_foV, 4.0f / 3.0f, 0.1f, 1000.0f);
	m_viewMatrix = glm::lookAt(
			m_position,
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
	);
}

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
	m_position = position;
	m_target = target;
	m_up = up;
	m_foV = 40.0f;
	m_projectionMatrix = glm::perspective(m_foV, 4.0f / 3.0f, 0.1f, 1000.0f);
	m_viewMatrix = glm::lookAt(
		m_position,
		target,
		up
	);
}

glm::vec3 Camera::getPosition() {
	return m_position;
}

glm::mat4 Camera::getProjectionMatrix() {
	return m_projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() {
	return m_viewMatrix;
}

void Camera::setCameraPosition(glm::vec3 position) {
	m_position = position;
}

void Camera::setCameraTarget(glm::vec3 target) {
	m_target = target;
	m_viewMatrix = glm::lookAt(
			m_position,
			m_target,
			m_up
	);
}

void Camera::setCameraTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
	m_position = position;
	m_target = target;
	m_up = up;
	m_viewMatrix = glm::lookAt(
			m_position,
			m_target,
			m_up
		);
}

void Camera::setCameraOrientation(float pitchAngle, float yawAngle, float rollAngle) {
	m_pitchAngle = pitchAngle;
	m_yawAngle = yawAngle;
	m_rollAngle = rollAngle;
}

void Camera::updateCameraAngles() {
	glm::vec3 camera_direction;

	// Convert the spherical coordinates to cartesian coordinates
	camera_direction.x = cos(m_pitchAngle) * sin(m_yawAngle);
	camera_direction.y = sin(m_pitchAngle);
	camera_direction.z = cos(m_pitchAngle) * cos(m_yawAngle);

	// Right vector in camera's coordinate space
	glm::vec3 right;

	right.x = sin(m_yawAngle - 3.14f/2.0f);
	right.y = 0;
	right.z = cos(m_yawAngle - 3.14f/2.0f);

	// Up vector in camera coordinate space
	m_up = glm::cross(right, camera_direction);
	m_target = m_position + camera_direction;

	m_viewMatrix = glm::lookAt(
			m_position,
			m_target,
			m_up
		);

}