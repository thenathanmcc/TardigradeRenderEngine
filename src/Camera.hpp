/**
 * Camera class definition
 * @author Nathan McCulloch
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:

	/* Default Constructor*/
	Camera();

	/* Constructor taking the camera position, target, and camera space up vectors*/
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

	/* Retrieve camera's position*/
	glm::vec3 getPosition();

	/* Retrieve camera's projection matrix */
	glm::mat4 getProjectionMatrix();

	/* Retrieve camera's view matrix */
	glm::mat4 getViewMatrix();

	/* Set the camera's position vector */
	void setCameraPosition(glm::vec3 position);

	/* Set the camera's target vector i.e the point it should look at */
	void setCameraTarget(glm::vec3 target);

	/* Set the camera's target vector */
	void setCameraTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up);

	/* Set the camera's orientation */
	void setCameraOrientation(float pitchAngle, float yawAngle, float rollAngle);



private:
	glm::vec3 m_position; // Camera's position
	glm::vec3 m_target;	  // Camera's target
	glm::vec3 m_up;		  // Camera Space Up vector


	// Euler Angles
	float m_pitchAngle; // rotation about x-axis
	float m_yawAngle;	// rotation about y-axis
	float m_rollAngle;	// rotation about z-axis
	

	float m_foV; // Field of View in radians

	glm::mat4 m_projectionMatrix; // View Space coordinates --> Clip space
	glm::mat4 m_viewMatrix;		  // World Space coordinates --> View Space

	/* Update the Camera Matrices with the Angles*/
	void updateCameraAngles();
};
#endif