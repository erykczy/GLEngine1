#include "engine/components/Transform.h"

#include "engine/GameObject.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform(GameObject* owner, Transform* ownerTransform) : Component(owner, ownerTransform) {
	scene = gameObject->scene;
}

glm::mat4 Transform::createModelMatrix() {
	glm::mat4 mat{ 1.0 };

	mat = glm::translate(mat, position);

	mat = glm::rotate(mat, eulerAngles.z, glm::vec3(0.0, 0.0, 1.0));
	mat = glm::rotate(mat, eulerAngles.y, glm::vec3(0.0, 1.0, 0.0));
	mat = glm::rotate(mat, eulerAngles.x, glm::vec3(1.0, 0.0, 0.0));

	mat = glm::scale(mat, scale);

	return mat;
}