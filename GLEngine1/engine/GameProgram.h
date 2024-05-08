#pragma once

struct GLFWwindow;
class Window;
class Scene;
class Input;

class GameProgram {
public:
	static GameProgram* s_runningProgram;
	Window* activeWindow{};
	Scene* activeScene{};
	Input* input{};

	GameProgram();

	virtual ~GameProgram();
	GameProgram(const GameProgram&) = delete;
	GameProgram& operator=(const GameProgram&) = delete;

	void startProgram();

protected:
	virtual void start() = 0;
	virtual void update() = 0;

private:
	void setupLibraries();
	void setupOpenGL();
	void renderLoop();
};
