#pragma once

#include "../../src/core/Game.hpp"

class ReflectionTest : public Game {
public:
	ReflectionTest();

private:
	std::unique_ptr<RenderComponent> m_skybox;
};
