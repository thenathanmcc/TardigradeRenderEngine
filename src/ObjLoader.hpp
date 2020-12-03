/*
 * Object Loader class definition
 * @author Nathan McCulloch
 * based on http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
 */



#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <glm/glm.hpp>
#include <vector>

class ObjLoader{
public:

	ObjLoader();

	bool loadOBJ(
		const char * path, 
		std::vector<glm::vec3> &out_vertices,
		std::vector<glm::vec2> &out_uvs,
		std::vector<glm::vec3> &out_normals
	);

};
#endif