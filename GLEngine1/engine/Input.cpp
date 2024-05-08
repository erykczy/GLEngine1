#include "engine/Input.h"

#include "engine/Window.h"
#include "engine/Debug.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace Input {
	GLFWwindow* m_window{};

	// mouse position last frame
	glm::vec3 m_lastFrameMousePos{};

	// mouse position this frame
	glm::vec3 m_frameMousePos{};

	// keys pressed this frame
	std::vector<int> m_frameKeysPressed{};

	// keys released this frame
	std::vector<int> m_frameKeysReleased{};

	// keys held (including pressed this frame)
	std::vector<int> m_keysHeld{};

	void initialize(Window* window) {
		m_window = window->m_glfw_window;

		double mouseX{}, mouseY{};
		glfwGetCursorPos(m_window, &mouseX, &mouseY);
		m_frameMousePos = glm::vec3(mouseX, mouseY, 1.0f);
		m_lastFrameMousePos = m_frameMousePos;

		glfwSetKeyCallback(m_window, onKeyEvent);
		glfwSetCursorPosCallback(m_window, onMousePosEvent);
	}

	void onFrameEnd() {
		m_frameKeysPressed.clear();
		m_frameKeysReleased.clear();
		m_lastFrameMousePos = m_frameMousePos;
	}

	void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			m_frameKeysPressed.push_back(key);
			m_keysHeld.push_back(key);
		}
		else if (action == GLFW_RELEASE) {
			m_frameKeysReleased.push_back(key);
			m_keysHeld.erase(std::find(m_keysHeld.begin(), m_keysHeld.end(), key));
		}
	}

	void onMouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			m_frameKeysPressed.push_back(-button-1);
			m_keysHeld.push_back(-button-1);
		}
		else if (action == GLFW_RELEASE) {
			m_frameKeysReleased.push_back(-button-1);
			m_keysHeld.erase(std::find(m_keysHeld.begin(), m_keysHeld.end(), -button-1));
		}
	}

	void onMousePosEvent(GLFWwindow* window, double posX, double posY) {
		m_frameMousePos.x = posX;
		m_frameMousePos.y = posY;
	}

	bool isKeyPressed(int key) {
		return std::find(m_frameKeysPressed.begin(), m_frameKeysPressed.end(), key) != m_frameKeysPressed.end();
	}

	bool isKeyDown(int key) {
		return std::find(m_keysHeld.begin(), m_keysHeld.end(), key) != m_keysHeld.end();
	}

	bool isKeyReleased(int key) {
		return std::find(m_frameKeysReleased.begin(), m_frameKeysReleased.end(), key) != m_frameKeysReleased.end();
	}

	bool isMouseButtonPressed(int button) {
		return std::find(m_frameKeysPressed.begin(), m_frameKeysPressed.end(), -button-1) != m_frameKeysPressed.end();
	}

	bool isMouseButtonDown(int button) {
		return std::find(m_keysHeld.begin(), m_keysHeld.end(), -button-1) != m_keysHeld.end();
	}

	bool isMouseButtonReleased(int button) {
		return std::find(m_frameKeysReleased.begin(), m_frameKeysReleased.end(), -button-1) != m_frameKeysReleased.end();
	}

	glm::vec3 getMousePos() {
		return m_frameMousePos;
	}

	glm::vec3 getMousePosDelta() {
		return m_frameMousePos - m_lastFrameMousePos;
	}

	void setCursorVisible(bool value) {
		glfwSetInputMode(m_window, GLFW_CURSOR, value ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
}
