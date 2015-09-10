#include "Entity.hpp"
#include "../components/BaseComponent.hpp"

void Entity::update(const Input &input, float delta) {
	for (auto& c: m_components) {
		c->update(input, delta);
	}

	for (auto& e : m_children) {
		e->update(input, delta);
	}
}

void Entity::render(const Renderer &renderer) {
	for (auto& c: m_components) {
		c->render(renderer);
	}

	for (auto& e : m_children) {
		e->render(renderer);
	}
}

void Entity::addChildEntity(std::unique_ptr<Entity>& entity) {
	m_children.emplace_back(std::move(entity));
}

void Entity::addChildEntity(Entity* entity) {
	m_children.emplace_back(entity);
}

void Entity::addComponent(std::unique_ptr<BaseComponent>& baseComponent) {
	baseComponent->setParentEntity(this);
	m_components.emplace_back(std::move(baseComponent));
}

void Entity::addComponent(BaseComponent* baseComponent) {
	baseComponent->setParentEntity(this);
	m_components.emplace_back(baseComponent);
}