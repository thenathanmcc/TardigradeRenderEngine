/*
 * Object class implementation
 * @author Nathan McCulloch
 */

#include "Object.hpp"
#include <iostream>

Object::Object() {
	m_rotationMatrix = glm::mat4(1.0f);
	m_translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;

	m_shader = NULL;
}


void Object::setObjectShader(Shader* shader) {
	if (m_shader != NULL)
		delete m_shader;

	m_shader = shader;
}

glm::mat4 Object::getTransformMatrix() {
	return m_transformMatrix;
}

void Object::addTransformMatrix(glm::mat4 mat) {
	m_transformMatrix = mat;
}

void Object::setTranslationMatrix(glm::mat4 mat) {
	m_translationMatrix = mat;
	m_translationMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void Object::setTranslationMatrix(glm::vec3 translationVector) {
	m_translationMatrix = glm::translate(glm::mat4(1.0f), translationVector);
	m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void Object::setScaleMatrix(glm::mat4 mat) {
	m_scaleMatrix = mat;
	m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void Object::setScaleMatrix(float scale) {
	m_scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

void Object::bindShaders() {
	m_shader->use();
}

void Object::unBindShaders() {

}