#pragma once

#include "../core/Input.hpp"
#include "../rendering/Renderer.hpp"
#include "../core/Entity.hpp"

class BaseComponent {
	friend class Entity;
public:
	BaseComponent() : m_parentEntity(nullptr) {}

	virtual void update(const Input& input, float delta) = 0;
	virtual void render(const Renderer& renderer) const = 0;
protected:
	inline const ModelToWorldTransform& getTransform() const { return m_parentEntity->getTransform(); }
	inline ModelToWorldTransform& getTransform() { return m_parentEntity->getTransform(); }
private:
	void setParentEntity(Entity* parent) { m_parentEntity = parent; }
	Entity* m_parentEntity;
};



