#include "CameraController.h"

#include "engine/Input.h"
#include "engine/components/Transform.h"
#include "engine/Debug.h"
#include "engine/Time.h"

#include <GLFW/glfw3.h>

void CameraController::update() {
	auto delta = Input::getMousePosDelta();
	transform->eulerAngles.x -= rotationSpeed * (-delta.y);
	transform->eulerAngles.y += rotationSpeed * delta.x;

	float speedMultiplier{ Time::getUnscaledDeltaTime() };

	if (Input::isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		speedMultiplier *= 2.0f;
	}

	if (Input::isKeyDown(GLFW_KEY_W)) {
		transform->position += speedMultiplier * movementSpeed * transform->getForward();
	}
	if (Input::isKeyDown(GLFW_KEY_S)) {
		transform->position -= speedMultiplier * movementSpeed * transform->getForward();
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		transform->position += speedMultiplier * movementSpeed * transform->getRight();
	}
	if (Input::isKeyDown(GLFW_KEY_A)) {
		transform->position -= speedMultiplier * movementSpeed * transform->getRight();
	}
	if (Input::isKeyDown(GLFW_KEY_SPACE)) {
		transform->position += speedMultiplier * movementSpeed * transform->getUp();
	}
	if (Input::isKeyDown(GLFW_KEY_LEFT_CONTROL)) {
		transform->position -= speedMultiplier * movementSpeed * transform->getUp();
	}
}