#pragma once

#include "../core/Input.hpp"
#include "../core/Entity.hpp"

class BaseComponent {
	friend class Entity;
public:
	BaseComponent() : m_parentEntity(nullptr) {}

	virtual void update(const Input& input, float delta) {}
	virtual void render(Shader& shader) const {}
	virtual void addToEngine(Engine* engine) {}

	inline const ModelToWorldTransform& getTransform() const { return m_parentEntity->getTransform(); }
protected:
	inline ModelToWorldTransform& getTransform() { return m_parentEntity->getTransform(); }
private:
	void setParentEntity(Entity* parent) { m_parentEntity = parent; }
	Entity* m_parentEntity;
};



