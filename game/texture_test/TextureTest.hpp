#pragma once

#include "../../src/core/Game.hpp"

class TextureTest : public Game {
public:
	TextureTest();

	std::unique_ptr<RenderComponent> m_skybox;
};



