/*
 * Controls class definition
 * @author Nathan McCulloch
 */



#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "Camera.hpp"


class Controls {

public:
	Controls() {};

	Controls(Camera* camera);

	/* Check for key presses and mouse movements and respond accordingly*/
	void checkUserInputs(GLFWwindow* window);

	/* Set Camera movement speed */
	void setCameraMovementSpeed(float speed);

	/* Set Camera rotating speed */
	void setCameraRotatingSpeed(float speed);

private:

	Camera* m_camera;			// Need camera reference
	float m_movementSpeed;		// Camera Movement X units / second
	float m_rotateSpeed;		// Camera Rotation X units / second

	float m_pitchAngle;			// Rotation angle around the x-axis
	float m_yawAngle;			// Rotation angle around the y-axis

	bool m_mouseFocus;			// Should track mouse
	double m_xcoord;			// Cursor x-coordinate
	double m_ycoord;			// Cursor y-coordinate

	int m_windowWidth;			// Width of window
	int m_windowHeight;			// Height of window
};
#endif