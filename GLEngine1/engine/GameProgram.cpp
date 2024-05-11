#include "engine/GameProgram.h"

#include "engine/AppConstants.h"
#include "engine/Window.h"
#include "engine/Scene.h"
#include "engine/Input.h"
#include "engine/Time.h"
#include "engine/Debug.h"
#include "libraries/stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

GameProgram* GameProgram::s_runningProgram{};

GameProgram::GameProgram() {
	if (s_runningProgram)
		throw std::runtime_error("Only 1 program can be instantiated!");
	s_runningProgram = this;

	// set up libraries
	setupLibraries();

	// set up window
	activeWindow = new Window{ AppConstants::defaultScreenWidth, AppConstants::defaultScreenHeight, AppConstants::windowTitle };

	// set up opengl
	setupOpenGL();

	// set up scene
	activeScene = new Scene{};

	// set up input
	Input::initialize(activeWindow);
}

GameProgram::~GameProgram() {
	delete activeScene;
	delete activeWindow;
}

void GameProgram::startProgram() {
	Input::setCursorVisible(false);

	// start render loop
	renderLoop();
}

void GameProgram::setupLibraries() {
	stbi_set_flip_vertically_on_load(true);
}

void GameProgram::setupOpenGL() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error{ "Failed to initialize GLAD!" };
	}

	glEnable(GL_DEPTH_TEST);
}

void GameProgram::renderLoop() {
	onSceneSetup();
	while (!activeWindow->isClosed()) {
		Time::onFrameStart();
		update();
		activeScene->update();

		activeScene->renderToActiveCamera();

		activeWindow->swapBuffers();
		Input::onFrameEnd();
		activeWindow->pollEvents();
	}
}

