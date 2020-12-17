/*
 * Mesh class definition
 * @author Nathan McCulloch
 */


#ifndef MESH_HPP
#define MESH_HPP


#include "Object.hpp"
#include <vector>

class Mesh: public Object {
public:
	Mesh(){};

	~Mesh();

	void setVertices(std::vector<float> vertices);

	void setVertices(std::vector<glm::vec3> vertices);

	void setUVs(std::vector<float> uvs);

	void setUVs(std::vector<glm::vec2> uvs);

	void setNormals(std::vector<glm::vec3> normals);

	void setIndices(std::vector<unsigned short> indices);

	void render(Camera* camera);

	void setMaterialIndex(int index);

	int  getMaterialIndex();

private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
	std::vector<unsigned short> m_indices;


	GLuint m_vertexBufferID;
	GLuint m_uvBufferID;
	GLuint m_normalBufferID;
	GLuint m_indexBufferID;
	int m_materialIndex;
};
#endif