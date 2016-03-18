#pragma once

#include "../../core/Game.hpp"

class TextureTest : public Game {
public:
	TextureTest(Engine* engine);
	std::unique_ptr<RenderComponent> m_skybox;
};



