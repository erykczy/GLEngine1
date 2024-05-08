#pragma once

#include "engine/components/Component.h"

class CameraController final : public Component {
public:
	using Component::Component;

	float movementSpeed{ 2.5f };
	float rotationSpeed{ 0.0012f };

	void update() override;
};