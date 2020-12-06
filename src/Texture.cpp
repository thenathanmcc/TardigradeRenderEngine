/*
 * Texture class implementation
 * @author Nathan McCulloch
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Texture.hpp"
#include "stb_image.h"

Texture::Texture(){

}

Texture::Texture(std::string textureFilePath) {
	m_textureID = loadTexture(textureFilePath);
}

GLuint Texture::getTextureID(){
	return m_textureID;
}

void Texture::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint Texture::loadTexture(const std::string textureFilePath) {
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char *data = stbi_load(textureFilePath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture: " << textureFilePath << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}