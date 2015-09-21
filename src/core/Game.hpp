#pragma once

#include "Input.hpp"
#include "RootEntity.hpp"

#include "../rendering/Camera.hpp"
#include "../rendering/Renderer.hpp"

class Engine;

class Game {
public:
	Game(Engine* engine);
	virtual ~Game() {}

	void update(const Input& input, float delta);
	void render(Renderer& renderer);
protected:
	RootEntity m_rootEntity;
	Camera m_camera;
private:
	const float m_CAMERA_SPEED;
	bool m_mouseGrabbed = false;
};

