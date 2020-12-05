/*
 * Scene class implementation
 * @author Nathan McCulloch
 */

#include "Scene.hpp"
#include <iostream>


Scene::Scene() {}

Scene::~Scene() {
	for (int i = 0; i < m_sceneObjects.size(); i++) {
		delete m_sceneObjects[i];
	}
	m_sceneObjects.clear();
}

void Scene::render(Camera* camera) {
	//std::cout << "Scene::render(Camera* camera) function called" << std::endl;
	for (int i = 0; i < m_sceneObjects.size(); i++){

        m_sceneObjects[i]->render(camera);
    }
}

void Scene::addObject(Object* newObject) {
	//std::cout << "Scene::addObject(Object* newObject) function called" << std::endl;
	m_sceneObjects.push_back(newObject);
}