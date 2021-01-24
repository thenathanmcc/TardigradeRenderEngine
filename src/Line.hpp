/*
 * Line class definition
 * @author Nathan McCulloch
 */


#ifndef Line_HPP
#define Line_HPP

#include <vector>
#include "Shader.hpp"
#include "Camera.hpp"

class Line {
public:

	Line ();

	Line (glm::vec3 start, glm::vec3 end, Shader* shader);

	void render(Camera* camera);

	void updateMVP(glm::mat4 mvp);

	void setColour(glm::vec3 colour);


private:
	GLuint m_vertexBuffer;
	GLfloat m_vertices[6];
	glm::vec3 m_startPoint;
	glm::vec3 m_endPoint;
	glm::mat4 m_MVP;
	glm::vec3 m_lineColour;

protected:
	Shader* m_shader;

};
#endif