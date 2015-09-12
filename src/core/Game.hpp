#pragma once

#include "Input.hpp"
#include "../rendering/Camera.hpp"
#include "Entity.hpp"

class Renderer;

class Game {
public:
	Game();
	virtual ~Game() {}

	void update(const Input& input, float delta);
	void render(Renderer& renderingEngine);
protected:
	Entity m_rootEntity;
	Camera m_camera;
private:
	const float m_CAMERA_SPEED;
	bool m_mouseGrabbed = false;
};

