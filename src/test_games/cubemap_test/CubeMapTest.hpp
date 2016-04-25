#pragma once

#include "../../core/Game.hpp"

class CubeMapTest : public Game {
public:
	CubeMapTest();

private:
	std::unique_ptr<RenderComponent> m_skybox;
};
