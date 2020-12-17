/*
 * Texture class definition
 * @author Nathan McCulloch
 */


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Texture {
public:

	Texture();

	Texture(std::string textureFilePath);

	~Texture();

	void bindTexture();

	GLuint getTextureID();

private:
	GLuint m_textureID;

	GLuint loadTexture(const std::string textureFilePath);
};
#endif