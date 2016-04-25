#pragma once

#include "../../core/Game.hpp"

class NormalTest : public Game {
public:
	NormalTest();

	void addCube(Entity& root, const Material& material, const glm::vec3& position);
};



