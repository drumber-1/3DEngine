#pragma once

#include "Input.hpp"
#include "RootEntity.hpp"

#include "../rendering/Renderer.hpp"
#include "GameWorld.hpp"

class Engine;

class Game {
public:
	Game();

	virtual ~Game() { }

	void update(const Input& input, float delta);

	void render(Renderer& renderer);

protected:
	GameWorld m_gameWorld;
};

