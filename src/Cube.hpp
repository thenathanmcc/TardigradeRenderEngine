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
#include "Texture.hpp"

class Cube: public Object {
public:

	Cube();

	Cube(std::string textureFilePath);

	~Cube();

	void init();

	void render(Camera* camera);

	void printMat4(glm::mat4 mat);

private:

	GLfloat m_vertex_buffer_data[30 * 6]; // 30 vertices per plane
	GLuint m_vertexBuffer;
	Texture* m_texture;
	GLuint m_textureID;
};
#endif