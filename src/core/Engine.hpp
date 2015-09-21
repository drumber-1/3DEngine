#pragma once


class Window;
class Renderer;
class Game;

class Engine {
public:
	Engine(double frameRate, Window* window, Renderer* renderingEngine);

	void start();
	void stop();

	inline Renderer* getRenderer() { return m_renderer; }

	inline void setGame(Game* game) { m_game = game; }
private:
	void update(double dt);
	void render();

	bool m_isRunning;
	double m_frameTime;
	Window* m_window;
	Renderer* m_renderer;
	Game* m_game;
};

