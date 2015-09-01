#include "Game.hpp"

#include <iostream>

#include "../rendering/Renderer.hpp"

Game::Game() : m_CAMERA_SPEED(0.5f) {
}

void Game::update(const Input& input, float delta) {
	if (input.getKeyPressed(SDL_SCANCODE_W)) {
		m_camera.moveForward(delta * m_CAMERA_SPEED);
	}
	if (input.getKeyPressed(SDL_SCANCODE_A)) {
		m_camera.moveLeft(delta * m_CAMERA_SPEED);
	}
	if (input.getKeyPressed(SDL_SCANCODE_S)) {
		m_camera.moveForward(-1 * delta * m_CAMERA_SPEED);
	}
	if (input.getKeyPressed(SDL_SCANCODE_D)) {
		m_camera.moveLeft(-1 * delta * m_CAMERA_SPEED);
	}
	if (input.getKeyPressed(SDL_SCANCODE_SPACE)) {
		m_camera.moveUp(delta * m_CAMERA_SPEED);
	}
	if (input.getKeyPressed(SDL_SCANCODE_LCTRL)) {
		m_camera.moveUp(-1 * delta * m_CAMERA_SPEED);
	}

	if (input.getKeyPressedLast(SDL_SCANCODE_ESCAPE)) {
		m_mouseGrabbed = false;
		input.showCursor(true);
	}

	glm::vec2 windowCenter = glm::vec2(input.getWindow().getWidth() / 2.0f, input.getWindow().getHeight() / 2.0f);

	if (!m_mouseGrabbed && input.getMousePressedLast(SDL_BUTTON_LEFT)) {
		m_mouseGrabbed = true;
		input.showCursor(false);
		input.setCursorPosition(windowCenter);
	} else if (m_mouseGrabbed) {
		float dx = windowCenter.x - input.getMousePositionX();
		float dy = windowCenter.y - input.getMousePositionY();
		m_camera.turnLeft(dx * 0.01f);
		m_camera.turnUp(dy * 0.01f);
		input.setCursorPosition(windowCenter);
	}
}

void Game::render(Renderer * renderingEngine) {
	renderingEngine->render(m_camera);
}
