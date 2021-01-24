/*
 * Line class implementation
 * @author Nathan McCulloch
 */

#include "Line.hpp"

Line::Line(){}

Line::Line(glm::vec3 start, glm::vec3 end, Shader* shader) {
	m_startPoint = start;
	m_endPoint = end;
	m_shader = shader;
	m_lineColour = glm::vec3(1.0f, 1.0f, 1.0f);

	GLfloat m_vertices[] = {
		start.x, start.y, start.z,
		end.x, end.y, end.z
	};

	//Generate, bind, and buffer vertex data
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void Line::render(Camera* camera) {
	m_shader->use();

	glm::mat4 MVP = camera->getViewProjectionMatrix() * glm::mat4(1.0f);

	//Pass MVP matrix to the GPU
	m_shader->updateMVPMatrix(MVP);
	m_shader->setVec3("colour", m_lineColour);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glDisable(GL_LIGHTING);
	glDrawArrays(GL_LINES, 0, 2);

	glEnable(GL_LIGHTING);
}

void Line::updateMVP(glm::mat4 mvp) {
	m_MVP = mvp;
}

void Line::setColour(glm::vec3 lineColour) {
	m_lineColour = lineColour;
}