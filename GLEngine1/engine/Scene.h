#pragma once
#include <vector>
#include "GameObject.h"
#include <glad/glad.h>

class Scene final {
public:
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	GameObject& createGameObject() {
		m_gameObjects.push_back(std::make_unique<GameObject>());
		return *(m_gameObjects.back());
	}
	
	void render();

	void update() {
		for (auto& element : m_gameObjects) element->update();
	}

private:
	std::vector<std::unique_ptr<GameObject>> m_gameObjects{};

};