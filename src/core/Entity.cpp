#include "Entity.hpp"
#include "../components/BaseComponent.hpp"

// Needed due to forward declaration of BaseComponent in header
// See: http://stackoverflow.com/questions/13414652/forward-declaration-with-unique-ptr
Entity::Entity() {}
Entity::~Entity() = default;

void Entity::update(const Input& input, float delta) {
	for (auto& c: m_components) {
		c->update(input, delta);
	}

	for (auto& e : m_children) {
		e->update(input, delta);
	}
}

void Entity::render(Shader& shader) const {
	for (auto& c : m_components) {
		c->render(shader);
	}

	for (auto& e : m_children) {
		e->render(shader);
	}
}

void Entity::addChildEntity(std::unique_ptr<Entity>& entity) {
	entity->setEngine(m_engine);
	m_children.emplace_back(std::move(entity));
}

void Entity::addChildEntity(Entity* entity) {
	entity->setEngine(m_engine);
	m_children.emplace_back(entity);
}

void Entity::addComponent(std::unique_ptr<BaseComponent>& baseComponent) {
	baseComponent->setParentEntity(this);
	//baseComponent->addToEngine(m_engine);
	m_components.emplace_back(std::move(baseComponent));
}

void Entity::addComponent(BaseComponent* baseComponent) {
	baseComponent->setParentEntity(this);
	//baseComponent->addToEngine(m_engine);
	m_components.emplace_back(baseComponent);
}

void Entity::setEngine(Engine* engine) {
	if (engine == m_engine) {
		return;
	}

	m_engine = engine;

	for (auto& c : m_components) {
		c->addToEngine(m_engine);
	}

	for (auto& e : m_children) {
		e->setEngine(m_engine);
	}
}
