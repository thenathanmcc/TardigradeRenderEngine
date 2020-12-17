/*
 * Material class definition. Used for representing a material
 * @author Nathan McCulloch
 */


#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Material {
public:
	Material();

	~Material();

	void setTextureName(const char* name);

	void setDiffuseColour(glm::vec3 colour);

	void setAmbientColour(glm::vec3 colour);

	void setSpecularColour(glm::vec3 colour);

	void setOpacity(float opacity);

	void setShininess(float shininess);


	glm::vec3 getDiffuseColour();
	glm::vec3 getAmbientColour();
	glm::vec3 getSpecularColour();
	float getOpacity();
	float getShininess();

	void setShader(Shader* shader);
	Shader* getShader();

	bool shaderIsInitialized();
	std::string getTextureName();

private:
	std::string m_textureName;

	glm::vec3 m_diffuseColour;
	glm::vec3 m_ambientColour;
	glm::vec3 m_specularColour;
	float m_opacity;
	float m_shininess;
	Shader* m_shader;

};
#endif