/*
 * CubeMap class implementation
 * @author Nathan McCulloch
 */



#include "CubeMap.hpp"
#include "stb_image.h"
#include <iostream>

CubeMap::CubeMap() {}


CubeMap::CubeMap(std::vector<std::string> faces, Shader* shader, int windowHeight, int windowWidth){
	m_faces = faces;
	m_shader = NULL;
	setShader(shader);
	m_shader->use();
	m_shader->setInt("skybox", 0);
	m_windowHeight = windowHeight;
	m_windowWidth = windowWidth;
	init();
	loadCubeMapTextures(m_faces);
}

void CubeMap::setShader(Shader* shader) {
	if (m_shader != NULL) {
		std::cout << m_shader << std::endl;
		std::cout << "here" << std::endl;
		delete m_shader;
	}
	m_shader = shader;
}

void CubeMap::init() {
	GLfloat m_vertex_buffer_data[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    //Generate, bind, and buffer vertex data
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);
}

void CubeMap::loadCubeMapTextures(std::vector<std::string> faces) {
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height, nrChannels;

	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char * data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else {
			std::cout << "TEXTURE_ERROR::FAILED TO LOAD CUBEMAP TEXTURE:\n" << faces[i] << "\n" << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::render(Camera* camera) {
	glDepthFunc(GL_LEQUAL);
	m_shader->use();

	glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);

	//Pass matrices to GPU
	m_shader->setMat4("view", view);
	m_shader->setMat4("projection", projection);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthFunc(GL_LESS);
}