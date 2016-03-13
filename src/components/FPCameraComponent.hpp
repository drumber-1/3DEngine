#pragma once

#include "CameraComponent.hpp"

#include "../rendering/Window.hpp"

class FPCameraComponent : public CameraComponent {
public:
	FPCameraComponent(float fov, float aspectRatio) : CameraComponent(fov, aspectRatio), m_CAMERA_SPEED(1.0f) {}

	virtual void update(const Input& input, float delta) {
		setAspectRatio(input.getWindow().getWidth() / (float)input.getWindow().getHeight());

		if (input.getKeyPressed(SDL_SCANCODE_W)) {
			getTransform().moveForward(delta * m_CAMERA_SPEED);
		}
		if (input.getKeyPressed(SDL_SCANCODE_A)) {
			getTransform().moveLeft(delta * m_CAMERA_SPEED);
		}
		if (input.getKeyPressed(SDL_SCANCODE_S)) {
			getTransform().moveForward(-1 * delta * m_CAMERA_SPEED);
		}
		if (input.getKeyPressed(SDL_SCANCODE_D)) {
			getTransform().moveLeft(-1 * delta * m_CAMERA_SPEED);
		}
		if (input.getKeyPressed(SDL_SCANCODE_SPACE)) {
			getTransform().moveUp(delta * m_CAMERA_SPEED);
		}
		if (input.getKeyPressed(SDL_SCANCODE_LCTRL)) {
			getTransform().moveUp(-1 * delta * m_CAMERA_SPEED);
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
			float dx = input.getMousePositionX() - windowCenter.x;
			float dy = input.getMousePositionY() - windowCenter.y;
			getTransform().turnLeft(dx * 0.01f);
			getTransform().turnUp(dy * 0.01f);
			input.setCursorPosition(windowCenter);
		}
	}

private:
	const float m_CAMERA_SPEED;
	bool m_mouseGrabbed = false;
};



