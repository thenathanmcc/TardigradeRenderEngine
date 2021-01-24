/*
 * Class for displaying a cube map
 * @author Nathan McCulloch
 */

#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <vector>
#include "Shader.hpp"
#include "Camera.hpp"

class CubeMap {
public:

	CubeMap();

	CubeMap(std::vector<std::string> faces, Shader* shader, int windowHeight, int windowWidth);

	void init();

	void setShader(Shader* shader);

	void loadCubeMapTextures(std::vector<std::string> faces);

	void render(Camera* camera);

private:
	GLuint m_vertexBuffer;					//Vertex Buffer ID
	GLfloat m_vertex_buffer_data[18 * 6]; 	//18 vertices per plane

	GLuint m_textureID;

	std::vector<std::string> m_faces; 		//File paths for all faces of the cube

	int m_windowHeight;
	int m_windowWidth;

protected:
	Shader* m_shader;						//Cubemap shader
};

#endif