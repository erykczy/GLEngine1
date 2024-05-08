#include "engine/GameProgram.h"

#include "engine/AppConstants.h"
#include "engine/Window.h"
#include "engine/Scene.h"
#include "libraries/stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

GameProgram* GameProgram::s_runningProgram{};

GameProgram::GameProgram() {
	if (s_runningProgram)
		throw std::runtime_error("Only 1 program can be instantiated!");
	s_runningProgram = this;
}

GameProgram::~GameProgram() {
	delete activeScene;
	delete activeWindow;
}

void GameProgram::startProgram() {
	setupWindow();
	setupLibraries();
	setupScene();
	renderLoop();
}

void GameProgram::setupLibraries() {
	setupOpenGL();

	stbi_set_flip_vertically_on_load(true);
}

void GameProgram::setupWindow() {
	activeWindow = new Window{ AppConstants::screenWidth, AppConstants::screenHeight, AppConstants::windowTitle };
}

void GameProgram::setupOpenGL() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error{ "Failed to initialize GLAD!" };
	}

	glEnable(GL_DEPTH_TEST);
}

void GameProgram::setupScene() {
	activeScene = new Scene{};
}

void GameProgram::renderLoop() {
	start();
	while (!activeWindow->isClosed()) {
		update();
		activeScene->update();

		activeScene->renderToActiveCamera();

		activeWindow->swapBuffers();
		activeWindow->pollEvents();
	}
}

