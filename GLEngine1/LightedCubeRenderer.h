#pragma once

#include "engine/components/Component.h"

class MeshRenderer;

class LightedCubeRenderer : public Component {
public:
	using Component::Component;

	Transform* mainLight{};

	void awake() override;
	void update() override;

private:
	MeshRenderer* m_meshRenderer{};
};