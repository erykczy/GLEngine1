#include "CameraController.h"

#include "engine/Input.h"
#include "engine/components/Transform.h"

#include <GLFW/glfw3.h>

void CameraController::update() {
	if (Input::isKeyDown(GLFW_KEY_UP)) {
		transform->eulerAngles.x -= rotationSpeed;
	}
	if (Input::isKeyDown(GLFW_KEY_DOWN)) {
		transform->eulerAngles.x += rotationSpeed;
	}
	if (Input::isKeyDown(GLFW_KEY_RIGHT)) {
		transform->eulerAngles.y += rotationSpeed;
	}
	if (Input::isKeyDown(GLFW_KEY_LEFT)) {
		transform->eulerAngles.y -= rotationSpeed;
	}
	/*if (Input::isKeyDown(GLFW_KEY_Q)) {
		transform->eulerAngles.z += rotationSpeed;
	}
	if (Input::isKeyDown(GLFW_KEY_E)) {
		transform->eulerAngles.z -= rotationSpeed;
	}*/

	if (Input::isKeyDown(GLFW_KEY_W)) {
		transform->position += movementSpeed * transform->getForward();
	}
	if (Input::isKeyDown(GLFW_KEY_S)) {
		transform->position -= movementSpeed * transform->getForward();
	}
	if (Input::isKeyDown(GLFW_KEY_D)) {
		transform->position += movementSpeed * transform->getRight();
	}
	if (Input::isKeyDown(GLFW_KEY_A)) {
		transform->position -= movementSpeed * transform->getRight();
	}
}