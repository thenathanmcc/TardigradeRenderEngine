/*
 * Simple cube object
 * @author Nathan McCulloch
 */


#ifndef CUBE_HPP
#define CUBE_HPP

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include "Object.hpp"

class Cube: public Object {
public:

	Cube();

	~Cube();

	void init();

	void render(Camera* camera);

private:

	GLfloat m_vertex_buffer_data[18 * 6];
	GLuint m_vertexBuffer;
};
#endif