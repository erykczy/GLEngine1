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

	GameObject& createGameObject();
	
	void update();

	void renderToActiveCamera();

	Camera* getActiveCamera() { return m_activeCamera; }
	void setActiveCamera(Camera* camera) { m_activeCamera = camera; }

	friend Camera;
private:
	std::vector<std::unique_ptr<GameObject>> m_gameObjects{};
	Camera* m_activeCamera{};

};