/*
 * Abstract object class definition
 * @author Nathan McCulloch
 */


#ifndef OBJECT_HPP
#define OBJECT_HPP


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"



class Object {
public:

	Object();

	virtual ~Object() {
		delete m_shader;
	}

	void setShader(Shader* shader);

	glm::mat4 getTransformMatrix();

	void addTransformMatrix(glm::mat4 mat);

	void setTranslationMatrix(glm::mat4 mat);

	void setTranslationMatrix(glm::vec3 translationVector);

	void setScaleMatrix(glm::mat4 mat);

	void setScaleMatrix(float scale);

	void bindShaders();

	void unBindShaders();

	virtual void render(Camera* camera) = 0;

private:
	std::string name;
	glm::mat4 m_transformMatrix;
	glm::mat4 m_rotationMatrix;
	glm::mat4 m_translationMatrix;
	glm::mat4 m_scaleMatrix;

protected:
	Shader* m_shader;
	
};
#endif