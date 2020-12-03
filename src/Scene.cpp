/*
 * Scene class implementation
 * @author Nathan McCulloch
 */

#include "Scene.hpp"


Scene::Scene() {}

Scene::~Scene() {
	for (int i = 0; i < m_sceneObjects.size(); i++) {
		delete m_sceneObjects[i];
	}
	m_sceneObjects.clear();
}

void Scene::render(Camera* camera) {
	for (int i = 0; i < m_sceneObjects.size(); i++){
        m_sceneObjects[i]->render(camera);
    }
}

void Scene::addObject(Object* newObject) {
	m_sceneObjects.push_back(newObject);
}