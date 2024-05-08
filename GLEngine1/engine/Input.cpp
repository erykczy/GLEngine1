#include "engine/Input.h"

#include "engine/Window.h"

#include <GLFW/glfw3.h>

Input* Input::s_input{};

Input::Input(Window* window) : m_window{ window->m_glfw_window } {
	if (s_input)
		throw std::runtime_error{ "Only 1 input handler can be instantiated!" };
	s_input = this;

	glfwSetKeyCallback(m_window, Input::static_onKeyEvent);
}

bool Input::isKeyPressed(int key) {
	return std::find(s_input->m_frameKeysPressed.begin(), s_input->m_frameKeysPressed.end(), key) != s_input->m_frameKeysPressed.end();
}
bool Input::isKeyDown(int key) {
	return std::find(s_input->m_keysHeld.begin(), s_input->m_keysHeld.end(), key) != s_input->m_keysHeld.end();
}
bool Input::isKeyReleased(int key) {
	return std::find(s_input->m_frameKeysReleased.begin(), s_input->m_frameKeysReleased.end(), key) != s_input->m_frameKeysReleased.end();
}

void Input::clearFrameData() {
	m_frameKeysPressed.clear();
	m_frameKeysReleased.clear();
}

void Input::onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		m_frameKeysPressed.push_back(key);
		m_keysHeld.push_back(key);
	}
	else if (action == GLFW_RELEASE) {
		m_frameKeysReleased.push_back(key);
		m_keysHeld.erase(std::find(m_keysHeld.begin(), m_keysHeld.end(), key));
	}
}

void Input::static_onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	s_input->onKeyEvent(window, key, scancode, action, mods);
}