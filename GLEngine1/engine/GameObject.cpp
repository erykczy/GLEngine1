#include "engine/GameObject.h"

#include "engine/components/Transform.h"

GameObject::GameObject(Scene* _scene) : scene{ _scene } {
	transform = &addComponent<Transform>();
	transform->transform = transform;
}

GameObject::~GameObject() {
	for (auto* component : m_components) {
		delete component;
	}
}

void GameObject::update() {
	for (auto* element : m_components) element->update();
}

void GameObject::render() {
	for (auto* element : m_components) element->render();
}