#include "engine/components/Transform.h"

#include "engine/GameObject.h"
#include "engine/Mathf.h"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform(GameObject* owner, Transform* ownerTransform) : Component(owner, ownerTransform) {
	scene = gameObject->scene;
}

glm::mat4 Transform::createModelMatrix() {
	glm::mat4 mat{ 1.0 };

	mat = glm::translate(mat, position);
	mat = Mathf::rotate(mat, eulerAngles);
	mat = glm::scale(mat, scale);

	return mat;
}

glm::vec3 Transform::localPositionToWorld(const glm::vec3& vec)
{
	return createModelMatrix() * glm::vec4(vec, 1.0f);
}

glm::vec3 Transform::localDirectionToWorld(const glm::vec3& vec)
{
	glm::mat4 mat{ 1.0 };
	mat = Mathf::rotate(mat, eulerAngles);

	return mat * glm::vec4(vec, 1.0f);
}

glm::vec3 Transform::getForward() {
	return Mathf::eulerAnglesToDirection(eulerAngles);
}

glm::vec3 Transform::getUp() {
	return Mathf::rotateVector(glm::vec3(0.0f, 1.0f, 0.0f), eulerAngles);
}

glm::vec3 Transform::getRight() {
	return Mathf::rotateVector(glm::vec3(1.0f, 0.0f, 0.0f), eulerAngles);
}
