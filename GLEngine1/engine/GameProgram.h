#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AppConstants.h"
#include "Scene.h"

class GameProgram {
public:
	GameProgram() = default;

	virtual ~GameProgram();
	GameProgram(const GameProgram&) = delete;
	GameProgram& operator=(const GameProgram&) = delete;

	void startProgram();

protected:
	Scene m_activeScene{};

	virtual void start() = 0;
	virtual void update() = 0;

private:
	GLFWwindow* m_window{};

	void setupWindow();
	void setupLibraries();
	void setupOpenGL();
	void renderLoop();

	static void onWindowSizeChanged(GLFWwindow* window, int width, int height);
};
