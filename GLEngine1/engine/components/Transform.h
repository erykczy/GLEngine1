#pragma once
#include "engine/components/Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class GameObject;
class Transform;
class Scene;

class Transform final : public Component {
public:
	Scene* scene{};

	Transform(GameObject* owner, Transform* ownerTransform);

	glm::vec3 position{};
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
	glm::vec3 eulerAngles{};

	glm::mat4 createModelMatrix();
};