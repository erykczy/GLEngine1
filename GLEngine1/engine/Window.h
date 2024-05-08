#pragma once
#include "engine/IEventSender.h"
#include "engine/IWindowEventListener.h"
#include "engine/Input.h"

#include <string_view>

struct GLFWwindow;

class Window final : public IEventSender<IWindowEventListener> {
public:
	static Window* s_activeWindow;

	Window(int width, int height, std::string_view title);

	~Window();

	void swapBuffers();
	void pollEvents();
	void close();
	bool isClosed() const { return m_closed; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	float getAspectRatio() const { return static_cast<float>(m_width) / m_height; }

	static void onWindowSizeChanged(GLFWwindow* window, int width, int height);

	friend void Input::initialize(Window* window);

private:
	GLFWwindow* m_glfw_window{};
	bool m_closed{ true };
	int m_width{};
	int m_height{};
};
