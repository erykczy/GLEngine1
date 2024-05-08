#pragma once
#include <stdexcept>
#include <vector>

class Window;
struct GLFWwindow;

class Input final {
public:
	static Input* s_input;

	Input(Window* window);

	static bool isKeyPressed(int key);
	static bool isKeyDown(int key);
	static bool isKeyReleased(int key);

	void clearFrameData();

private:
	GLFWwindow* m_window{};

	// keys pressed this frame
	std::vector<int> m_frameKeysPressed{};

	// keys released this frame
	std::vector<int> m_frameKeysReleased{};

	// keys held (including pressed this frame)
	std::vector<int> m_keysHeld{};

	void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void static_onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};