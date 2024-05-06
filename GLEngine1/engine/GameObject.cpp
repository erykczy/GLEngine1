#include "GameObject.h"

GameObject::~GameObject() {
	for (auto* component : m_components) {
		delete component;
	}
}