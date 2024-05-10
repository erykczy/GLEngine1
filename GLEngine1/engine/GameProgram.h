#pragma once

struct GLFWwindow;
class Window;
class Scene;

class GameProgram {
public:
	static GameProgram* s_runningProgram;
	Window* activeWindow{};
	Scene* activeScene{};

	GameProgram();

	virtual ~GameProgram();
	GameProgram(const GameProgram&) = delete;
	GameProgram& operator=(const GameProgram&) = delete;

	void startProgram();

protected:
	virtual void setupScene() = 0;
	virtual void update() = 0;

private:
	void setupLibraries();
	void setupOpenGL();
	void renderLoop();
};
