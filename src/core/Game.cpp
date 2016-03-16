#include "Game.hpp"

Game::Game(Engine* engine) : m_gameWorld(engine) { }

void Game::update(const Input& input, float delta) {
	m_gameWorld.rootEntity.update(input, delta);
}

void Game::render(Renderer& renderer) {
	renderer.render(m_gameWorld);
}
