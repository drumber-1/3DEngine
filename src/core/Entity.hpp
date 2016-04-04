#pragma once

#include <memory>
#include <vector>

#include "Input.hpp"
#include "ModelToWorldTransform.hpp"

class BaseComponent;

class Engine;

class Shader;

class Entity {
public:
	Entity();

	~Entity();

	void update(const Input& input, float delta);

	void render(Shader& shader) const;

	void addChildEntity(std::unique_ptr<Entity>& entity);

	void addChildEntity(Entity* entity);

	void addComponent(std::unique_ptr<BaseComponent>& baseComponent);

	void addComponent(BaseComponent* baseComponent);

	inline ModelToWorldTransform& getLocalTransform() { return transform; }

	const glm::mat4 getTransformationMatrix() const;

	const glm::mat4 getCameraMatrix() const;

	const glm::vec3 getPosition() const;

	const glm::vec3 getDirection() const;

	const glm::quat getRotation() const;

protected:
	Entity(Engine* engine) : m_engine(engine) { }

private:
	std::vector<std::unique_ptr<Entity>> m_children;
	Entity* m_parent = nullptr;
	std::vector<std::unique_ptr<BaseComponent>> m_components;
	ModelToWorldTransform transform;
	Engine* m_engine;

	void setEngine(Engine* engine);
};



