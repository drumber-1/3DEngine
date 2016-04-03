#pragma once

#include "../core/Input.hpp"
#include "../core/Entity.hpp"

class BaseComponent {
	friend class Entity;
public:
	BaseComponent() : m_parentEntity(nullptr) {}

	virtual void update(const Input& input, float delta) {}
	virtual void render(Shader& shader) const {}
	virtual void addToEngine(Engine* engine) const {}

	inline const glm::mat4 getTransformationMatrix() const { return m_parentEntity->getTransformationMatrix(); }
	inline const glm::mat4 getCameraMatrix() const { return m_parentEntity->getCameraMatrix(); }
	inline const glm::vec3 getPosition() const { return m_parentEntity->getPosition(); }
	inline const glm::vec3 getDirection() const { return m_parentEntity->getDirection(); }
	inline const glm::quat getRotation() const { return m_parentEntity->getRotation(); }
protected:
	inline ModelToWorldTransform& getTransform() { return m_parentEntity->getLocalTransform(); }
	virtual void setParentEntity(Entity* parent) { m_parentEntity = parent; }
private:
	Entity* m_parentEntity;
};



