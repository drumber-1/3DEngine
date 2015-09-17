#pragma once

class Window;
class Renderer;
class Game;

class Engine {
public:
	Engine(double frameRate, Window* window, Renderer * renderingEngine, Game* game);

	void start();
	void stop();

	inline Renderer* getRenderingEngine() { return m_renderingEngine; }
private:
	void update(double dt);
	void render();

	bool m_isRunning;
	double m_frameTime;
	Window* m_window;
	Renderer* m_renderingEngine;
	Game* m_game;
};

