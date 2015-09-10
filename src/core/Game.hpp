#pragma once

#include "Input.hpp"
#include "../rendering/Camera.hpp"

class Renderer;

class Game {
public:
	Game();
	virtual ~Game() {}

	void update(const Input& input, float delta);
	void render(Renderer& renderingEngine);

private:
	Camera m_camera;
	const float m_CAMERA_SPEED;
	bool m_mouseGrabbed = false;
};

