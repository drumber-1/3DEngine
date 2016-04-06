#pragma once

#include "../../core/Game.hpp"

class ShadowTest : public Game {
public:
	ShadowTest(Engine* engine);

	void addCube(Entity& root, const Material& material, const glm::vec3& position, const glm::vec3& scale);

private:
	const int ROOM_WIDTH = 4;
	const int ROOM_HEIGHT = 4;
};