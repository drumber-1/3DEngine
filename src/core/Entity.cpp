#include "Entity.hpp"
#include "../components/BaseComponent.hpp"

// Needed due to forward declaration of BaseComponent in header
// See: http://stackoverflow.com/questions/13414652/forward-declaration-with-unique-ptr
Entity::Entity() { }

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
		//shader.draw(c);
	}

	for (auto& e : m_children) {
		e->render(shader);
	}
}

void Entity::addChildEntity(std::unique_ptr<Entity>& entity) {
	entity->setEngine(m_engine);
	entity->m_parent = this;
	m_children.emplace_back(std::move(entity));
}

void Entity::addChildEntity(Entity* entity) {
	entity->setEngine(m_engine);
	entity->m_parent = this;
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

const glm::mat4 Entity::getTransformationMatrix() const {
	if (m_parent == nullptr) {
		return transform.getTransformationMatrix();
	} else {
		return m_parent->getTransformationMatrix() * transform.getTransformationMatrix();
	}
}

const glm::mat4 Entity::getCameraMatrix() const {
	if (m_parent == nullptr) {
		return transform.getCameraMatrix();
	} else {
		return m_parent->getCameraMatrix() * transform.getCameraMatrix();
	}
}

const glm::vec3 Entity::getPosition() const {
	glm::mat4 trans = getTransformationMatrix();
	return glm::vec3(trans[3]);
}

const glm::vec3 Entity::getDirection() const {
	return getRotation() * glm::vec3(0.0f, 0.0f, -1.0f);
}

const glm::quat Entity::getRotation() const {
	glm::quat rot(getTransformationMatrix());
	return rot;
}
