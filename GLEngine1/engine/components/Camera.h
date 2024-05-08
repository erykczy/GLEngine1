#pragma once
#include "engine/components/Component.h"

#include "engine/IWindowEventListener.h"
#include "engine/AppConstants.h"

#include <glm/mat4x4.hpp>
#include <iostream>
#include <engine/Debug.h>

class Window;

class Camera final : public Component, public IWindowEventListener {
public:
	using Component::Component;

	void renderScene();

	glm::mat4 createViewMatrix();

	// returns fov in radians
	float getFov() const { return m_fovRadians; }
	// sets fov in radians
	void setFov(float valueRadians);
	float getNearPlane() const { return m_nearPlane; }
	void setNearPlane(float value);
	float getFarPlane() const { return m_nearPlane; }
	void setFarPlane(float value);
	void setAspectRatio(float value);
	void setAutoAspectRatio(bool value);

	void onWindowSizeChanged(Window* window) override {
		Debug::logInfo("Window size changed! width: ");
	}

private:
	glm::mat4 m_projectionMatrix{};
	float m_fovRadians{ AppConstants::defaultCameraFov };
	float m_nearPlane{ AppConstants::defaultCameraNearPlane };
	float m_farPlane{ AppConstants::defaultCameraFarPlane };
	bool m_autoAspectRatio{};
	float m_aspectRatio{};

	void updateProjectionMatrix();
};