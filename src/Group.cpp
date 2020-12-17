/*
 * Group class implementation
 * @author Nathan McCulloch
 */


#include "Group.hpp"
#include <iostream>

Group::Group() {
	init();
}

Group::~Group(){

}

void Group::addMesh(Mesh* mesh) {
	m_meshes.push_back(mesh);
}

void Group::addMaterial(Material* material) {
	m_materials.push_back(material);
}

Mesh* Group::getMesh(int index) {
	return m_meshes[index];
}

Material* Group::getMaterial(int index) {
	return m_materials[index];
}

int Group::getNumMeshes() {
	return m_meshes.size();
}

void Group::setRenderMode(float renderMode) {
	for (int i = 0; i < m_materials.size(); i++) {
		Shader* shader = m_materials[i]->getShader();
		if (shader != NULL) {
			shader->setRenderMode(renderMode);
		}
	}
}

void Group::init() {
	setupShaders();
}

void Group::render(Camera* camera) {
	if (m_meshes.size() > 0) {
		int meshIndex = 0;
		while (meshIndex < m_meshes.size()) {
			m_meshes[meshIndex]->bindShaders();
			m_meshes[meshIndex]->render(camera);
			meshIndex++;
		}
	}
}

void Group::setupShaders() {
	if (m_meshes.size() > 0) {
		int meshIndex = 0;
		int materialIndex;
		while (meshIndex < m_meshes.size()) {
			materialIndex = m_meshes[meshIndex]->getMaterialIndex();
			Material* material = getMaterial(materialIndex);

			Shader* shader = NULL;
			if (!material->shaderIsInitialized()) {
				shader = new Shader("./src/shaders/mtlShader.vert", "./src/shaders/mtlShader.frag");
				shader->setDiffuseColour(material->getDiffuseColour());
				shader->setAmbientColour(material->getAmbientColour());
				shader->setSpecularColour(material->getSpecularColour());
				shader->setOpacity(material->getOpacity());
				material->setShader(shader);
				if (material->getTextureName() != "") {
					Texture* texture = new Texture(material->getTextureName());
					shader->setTexture(texture);
				}

			} else {
				shader = material->getShader();
			}
			m_meshes[meshIndex]->setShader(shader);
			meshIndex++;
		}
	}
}