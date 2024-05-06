#include "GameProgram.h"
#include <iostream>

GameProgram::~GameProgram() {
	glfwTerminate();
}

void GameProgram::startProgram() {
	setupWindow();
	setupOpenGL();
	renderLoop();
}

void GameProgram::renderLoop() {
	start();
	while (!glfwWindowShouldClose(m_window)) {
		update();
		m_activeScene.update();

		m_activeScene.render();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void GameProgram::setupWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, AppConstants::openGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, AppConstants::openGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	m_window = glfwCreateWindow(AppConstants::screenWidth, AppConstants::screenHeight, AppConstants::windowTitle, NULL, NULL);
	if (m_window == NULL) throw std::runtime_error{ "Failed to create GLFW window!" };
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, onWindowSizeChanged);
}

void GameProgram::setupOpenGL() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error{ "Failed to initialize GLAD!" };
	}
}

void GameProgram::onWindowSizeChanged(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}