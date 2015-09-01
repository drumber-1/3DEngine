#include "Engine.hpp"

#include <iostream>

#include "../rendering/Window.hpp"
#include "../rendering/Renderer.hpp"

#include "Time.hpp"
#include "Game.hpp"

Engine::Engine(double frameRate,
			   Window* window,
			   Renderer* renderingEngine,
			   Game* game) :
		m_isRunning(false),
		m_frameTime(1 / frameRate),
		m_window(window),
		m_renderingEngine(renderingEngine),
		m_game(game) {
}

void Engine::start() {
	if (m_isRunning) {
		return;
	}

	m_isRunning = true;

	double lastFrameStartTime = Time::getTime();
	double frameDebt = 0.0;

	int frames = 0;
	double fpsTimer = 0.0;

	while (m_isRunning) {
		double frameStartTime = Time::getTime();
		double lastFrameTime = frameStartTime - lastFrameStartTime;
		lastFrameStartTime = frameStartTime;

		frameDebt += lastFrameTime / m_frameTime;
		fpsTimer += lastFrameTime;

		bool renderNeeded = false;
		while (frameDebt > 1.0) {
			update(m_frameTime);

			if (fpsTimer > 1.0) {
				std::cout << frames << " fps\n";
				fpsTimer -= 1.0;
				frames = 0;
			}

			renderNeeded = true;
			frameDebt -= 1.0;
		}

		if (renderNeeded) {
			render();
			frames++;
		} else {
			Time::sleep(1);
		}

	}
}

void Engine::stop() {
	m_isRunning = false;
}

void Engine::update(double dt) {
	m_window->update();
	if (m_window->isCloseRequested()) {
		stop();
	}
	m_game->update(m_window->getInput(), dt);
}

void Engine::render() {
	m_game->render(m_renderingEngine);
	m_window->swapBuffers();
}
