#pragma once
#include <vector>
#include <memory>
#include "components/Component.h"

class GameObject final {
public:
	GameObject() = default;
	~GameObject();

	GameObject(const GameObject& source) = delete;
	GameObject& operator=(const GameObject&) = delete;

	template<typename T>
	T& getComponent() const;

	template<typename T>
	T& addComponent();

	void update() {
		for (auto* element : m_components) element->update();
	}

	void render() {
		for (auto* element : m_components) element->render();
	}

private:
	std::vector<Component*> m_components{};
};

template<typename T>
T& GameObject::getComponent() const {
	for (auto* component : m_components) {
		auto* castedComponent{ dynamic_cast<T*>(component) };
		if (castedComponent != nullptr) return *castedComponent;
	}
	return nullptr;
}

template<typename T>
T& GameObject::addComponent() {
	auto* comp{ new T{} };
	m_components.push_back(comp);
	return *comp;
}