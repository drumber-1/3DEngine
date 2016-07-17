#pragma once

#include "../../src/core/Game.hpp"

class Showcase : public Game {
public:
	Showcase();

	void addCube(Entity& root, const Material& material, const glm::vec3& position, const glm::vec3& scale);

private:
	const int ROOM_WIDTH = 5;
	const int ROOM_HEIGHT = 4;

	std::unique_ptr<RenderComponent> m_skybox;
};