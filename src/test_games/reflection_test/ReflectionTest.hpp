#pragma once

#include "../../core/Game.hpp"

class ReflectionTest : public Game {
public:
	ReflectionTest();

private:
	std::unique_ptr<RenderComponent> m_skybox;
};
