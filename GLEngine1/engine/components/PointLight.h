#pragma once

#include "engine/components/Component.h"

#include <glm/vec3.hpp>

class PointLight : public Component {
public:
	glm::vec3 ambient{};
	glm::vec3 diffuse{};
	glm::vec3 specular{};
	float constant{};
	float linear{};
	float quadratic{};
	
	using Component::Component;
};