#include "engine/components/Camera.h"

#include "engine/components/Transform.h"
#include "engine/Scene.h"
#include "engine/GameObject.h"
#include "engine/Debug.h"
#include "engine/Window.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>

void Camera::awake() {
	updateProjectionMatrix();
}

void Camera::renderScene() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& element : transform->scene->m_gameObjects)
		element->render(this);
}

glm::mat4 Camera::createViewMatrix() const {
	return glm::lookAt(transform->position, transform->position + transform->getForward(), transform->getUp());;
}

void Camera::updateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(m_fovRadians, m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::setFov(float valueRadians) {
	m_fovRadians = valueRadians;
	updateProjectionMatrix();
}

void Camera::setNearPlane(float value) {
	m_nearPlane = value;
	updateProjectionMatrix();
}

void Camera::setFarPlane(float value) {
	m_farPlane = value;
	updateProjectionMatrix();
}

void Camera::setAspectRatio(float value) {
	if (m_autoAspectRatio)
		Debug::log(Debug::warning, "You are trying to change aspect ratio while it is updated automatically. Change autoAspectRatio value!");
	m_aspectRatio = value;
	updateProjectionMatrix();
}

void Camera::setAutoAspectRatio(bool value) {
	m_autoAspectRatio = value;
	if (m_autoAspectRatio) {
		m_aspectRatio = Window::s_activeWindow->getAspectRatio();
		Window::s_activeWindow->addListener(this);
	}
	else {
		Window::s_activeWindow->removeListener(this);
	}
}

void Camera::onWindowSizeChanged(Window* window) {
	m_aspectRatio = window->getAspectRatio();
	updateProjectionMatrix();
}