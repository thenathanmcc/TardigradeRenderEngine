/*
 * Scene class definition.
 * @author Nathan McCulloch
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Object.hpp"
#include "Camera.hpp"


class Scene {
public:

	Scene();

	~Scene();

	void render(Camera* camera);

	void addObject(Object* object);

private:
	std::vector<Object*> m_sceneObjects;
};
#endif