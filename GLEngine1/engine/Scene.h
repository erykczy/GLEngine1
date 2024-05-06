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
		return m_gameObjects.emplace_back();
	}
	
	void render() {
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& element : m_gameObjects) element.render();
	}

	void update() {
		for (auto& element : m_gameObjects) element.update();
	}

private:
	std::vector<GameObject> m_gameObjects{};

};