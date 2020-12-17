/*
 * Mesh class implementation
 * @author Nathan McCulloch
 */


#include "Mesh.hpp"
#include "Camera.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Mesh::~Mesh(){
	glDeleteBuffers(1, &m_vertexBufferID);
    glDeleteBuffers(1, &m_uvBufferID);
    glDeleteBuffers(1, &m_normalBufferID);
    glDeleteBuffers(1, &m_indexBufferID);
};

void Mesh::setVertices(std::vector<float> vertices) {
	m_vertices.clear(); // Clear vector if not empty
	for (int i = 0; i < vertices.size() / 3; i++) {
		m_vertices.push_back(glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
	}

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
}

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
	m_vertices.clear();
	m_vertices.resize(vertices.size());
	std::copy(vertices.begin(), vertices.end(), m_vertices.begin());

	glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);
}

void Mesh::setUVs(std::vector<float> uvs) {
	m_uvs.clear();
	for (int i = 0; i < uvs.size() / 2; i++) {
		//m_uvs.push_back(glm::vec2(uvs[i * 2], uvs[i * 2 + 1]));
		m_uvs.push_back(glm::vec2(uvs[i*2+0],uvs[i*2+1]));
	}

	glGenBuffers(1, &m_uvBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);
}

void Mesh::setUVs(std::vector<glm::vec2> uvs) {
	m_uvs.clear();
	m_uvs.resize(uvs.size());
	std::copy(uvs.begin(), uvs.end(), m_uvs.begin());

	glGenBuffers(1, &m_uvBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);
}

void Mesh::setNormals(std::vector<glm::vec3> normals) {
	m_normals.clear();
	m_normals.resize(normals.size());

	std::copy(normals.begin(), normals.end(), m_normals.begin());

	glGenBuffers(1, &m_normalBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
}


void Mesh::setIndices(std::vector<unsigned short> indices) {
	m_indices.clear();
	m_indices.resize(indices.size());

	std::copy(indices.begin(), indices.end(), m_indices.begin());

	glGenBuffers(1, &m_indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
}

void Mesh::render(Camera* camera) {
	bindShaders();

	glm::mat4 modelMatrix = this->getTransformMatrix();
	glm::mat4 MVP = camera->getViewProjectionMatrix() * modelMatrix;
	glm::mat4 viewMatrix = camera->getViewMatrix();

	//Send new matrices to the GPU
	m_shader->updateModelMatrix(modelMatrix);
	m_shader->updateViewMatrix(viewMatrix);
	m_shader->updateMVPMatrix(MVP);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	if (m_uvs.size() != 0) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBufferID);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	}

	if (m_normals.size() != 0) {
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferID);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	}

	if (m_indices.size() == 0) {
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	} else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	}

	glDisableVertexAttribArray(0);
	if (m_uvs.size() != 0)
		glDisableVertexAttribArray(1);
	if (m_normals.size() != 0)
		glDisableVertexAttribArray(2);

}

void Mesh::setMaterialIndex(int index) {
	m_materialIndex = index;
}

int Mesh::getMaterialIndex() {
	return m_materialIndex;
}