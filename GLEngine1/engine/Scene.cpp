#include "engine/Scene.h"

#include "engine/GameObject.h"
#include "engine/components/Camera.h"
#include "engine/Debug.h"

GameObject& Scene::createGameObject(const glm::vec3& position) {
	m_gameObjects.push_back(std::make_unique<GameObject>(this, position));
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
		Debug::logger << "There is no active camera!" << Debug::endWarning;
	}
}