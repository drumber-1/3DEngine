#pragma once

#include "Input.hpp"
#include "RootEntity.hpp"

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
	const CameraComponent* m_currentCamera;
};

