#pragma once

#include "engine/GameObject.h"

#include <vector>
#include <memory>

class Camera;

class Scene final {
public:
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	GameObject& createGameObject(const glm::vec3& position);
	
	void update();

	void renderToActiveCamera();

	Camera* getActiveCamera() { return m_activeCamera; }
	void setActiveCamera(Camera* camera) { m_activeCamera = camera; }

	template<typename T>
	std::vector<T*> getGameObjects();

	friend Camera;
private:
	std::vector<std::unique_ptr<GameObject>> m_gameObjects{};
	Camera* m_activeCamera{};

};

template<typename T>
std::vector<T*> Scene::getGameObjects() {
	std::vector<T*> vec{};
	for (auto& gameObject : m_gameObjects) {
		auto* comp{ gameObject->getComponent<T>() };
		if (comp)
			vec.push_back(comp);
	}
	return vec;
}