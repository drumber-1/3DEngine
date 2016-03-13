#include "Game.hpp"

Game::Game(Engine* engine) : m_rootEntity(engine) { }

void Game::update(const Input& input, float delta) {
	m_rootEntity.update(input, delta);
}

void Game::render(Renderer& renderer) {
	renderer.render(*m_currentCamera, m_rootEntity);
}
