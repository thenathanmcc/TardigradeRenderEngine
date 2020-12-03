/*
 * Texture class definition
 * @author Nathan McCulloch
 */


#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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