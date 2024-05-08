#pragma once

#include "engine/components/Component.h"

class CameraController final : public Component {
public:
	using Component::Component;

	float movementSpeed{ 0.01f };
	float rotationSpeed{ 0.01f };

	void update() override;
};