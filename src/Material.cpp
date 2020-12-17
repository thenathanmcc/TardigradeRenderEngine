/*
 * Material class implementation
 * @author Nathan McCulloch
 */


#include "Material.hpp"

Material::Material() {
	m_shader = NULL;
}

Material::~Material() {

}

void Material::setTextureName(const char* name) {
	m_textureName = std::string(name);
}

void Material::setDiffuseColour(glm::vec3 colour) {
	m_diffuseColour = colour;
}

void Material::setAmbientColour(glm::vec3 colour) {
	m_ambientColour = colour;
}

void Material::setSpecularColour(glm::vec3 colour) {
	m_specularColour = colour;
}

void Material::setOpacity(float opacity) {
	m_opacity = opacity;
}

void Material::setShininess(float shininess) {
	m_shininess = shininess;
}

glm::vec3 Material::getDiffuseColour() {
	return m_diffuseColour;
}

glm::vec3 Material::getAmbientColour() {
	return m_ambientColour;
}

glm::vec3 Material::getSpecularColour() {
	return m_specularColour;
}

float Material::getOpacity() {
	return m_opacity;
}

float Material::getShininess() {
	return m_shininess;
}

void Material::setShader(Shader* shader) {
	m_shader = shader;
}

Shader* Material::getShader() {
	return m_shader;
}

bool Material::shaderIsInitialized(){
	return (m_shader != NULL);
}

std::string Material::getTextureName() {
	return m_textureName;
}