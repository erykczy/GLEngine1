#pragma once

#include <glm/vec3.hpp>
#include <vector>

class Scene;
class Transform;
class Component;
class Camera;

class GameObject final {
public:
	Transform* transform{};
	Scene* scene{};

	GameObject(Scene* _scene, const glm::vec3& position);
	~GameObject();

	GameObject(const GameObject& source) = delete;
	GameObject& operator=(const GameObject&) = delete;

	template<typename T>
	T* getComponent() const;

	template<typename T>
	T* addComponent();

	void update();
	void render(Camera* camera);

private:
	std::vector<Component*> m_components{};
};

template<typename T>
T* GameObject::getComponent() const {
	for (auto* component : m_components) {
		auto* castedComponent{ dynamic_cast<T*>(component) };
		if (castedComponent != nullptr) return castedComponent;
	}
	return nullptr;
}

template<typename T>
T* GameObject::addComponent() {
	auto* comp{ new T{ this, transform } };
	m_components.push_back(comp);
	comp->awake();
	return comp;
}
