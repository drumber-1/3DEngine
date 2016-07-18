#pragma once

#include "../../src/core/Game.hpp"

#include <string>

class ShadowTest : public Game {
public:
	ShadowTest();

	void addObject(Entity& root, const std::string& model, const Material& material, const glm::vec3& position, const glm::vec3& scale, bool orbit);

private:
	const int ROOM_WIDTH = 10;
	const int ROOM_HEIGHT = 10;
};