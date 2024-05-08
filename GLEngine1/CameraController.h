#pragma once

#include "engine/components/Component.h"

class CameraController final : public Component {
public:
	using Component::Component;

	float movementSpeed{ 0.05f };
	float rotationSpeed{ 0.001f };

	void update() override;
};