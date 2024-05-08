#pragma once
#include <glm/trigonometric.hpp>

namespace AppConstants {
	inline constexpr int openGLVersionMajor{ 4 };
	inline constexpr int openGLVersionMinor{ 6 };
	inline constexpr int screenWidth{ 800 };
	inline constexpr int screenHeight{ 600 };
	inline constexpr float defaultCameraFov{ glm::radians(45.0f) };
	inline constexpr float defaultCameraNearPlane{ 0.1f };
	inline constexpr float defaultCameraFarPlane{ 100.1f };
	inline constexpr const char* windowTitle{ "Game" };
}