#include "engine/Window.h"

#include "engine/AppConstants.h"

#include <GLFW/glfw3.h>

#include <stdexcept>

Window* Window::s_activeWindow{};

void Window::onWindowSizeChanged(GLFWwindow* glfwWindow, int width, int height) {
	glViewport(0, 0, width, height);
	Window& window = *Window::s_activeWindow;
	window.m_width = width;
	window.m_height = height;
	window.notifyListeners([](IWindowEventListener* l) { l->onWindowSizeChanged(Window::s_activeWindow); });
}

Window::Window(int width, int height, std::string_view title) {
	if (s_activeWindow)
		throw std::runtime_error{ "Only 1 window can be instantiated!" };
	s_activeWindow = this;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, AppConstants::openGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, AppConstants::openGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	m_glfw_window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
	if (m_glfw_window == NULL) throw std::runtime_error{ "Failed to create GLFW window!" };
	glfwMakeContextCurrent(m_glfw_window);
	glfwSetFramebufferSizeCallback(m_glfw_window, Window::onWindowSizeChanged);

	m_closed = false;
	m_width = width;
	m_height = height;
}

Window::~Window() {
	close();
	glfwTerminate();
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_glfw_window);
}

void Window::pollEvents() {
	glfwPollEvents();

	if (glfwWindowShouldClose(m_glfw_window))
		close();
}

void Window::close() {
	glfwSetWindowShouldClose(m_glfw_window, true);
	m_closed = true;
}

