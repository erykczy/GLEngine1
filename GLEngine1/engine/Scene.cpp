#include "engine/Scene.h"

#include "engine/GameObject.h"
#include "engine/components/Camera.h"
#include "engine/Debug.h"

GameObject& Scene::createGameObject() {
	m_gameObjects.push_back(std::make_unique<GameObject>(this));
	return *(m_gameObjects.back());
}

void Scene::update() {
	for (auto& element : m_gameObjects) element->update();
}

void Scene::renderToActiveCamera() {
	if (m_activeCamera) {
		m_activeCamera->renderScene();
	}
	else {
		Debug::logInfo("There is no active camera!");
	}
}