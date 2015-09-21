#pragma once

#include <memory>
#include <vector>

#include "Input.hpp"
#include "ModelToWorldTransform.hpp"

#include "../rendering/shader/PhongShader.hpp"

class BaseComponent;
class Engine;

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

	inline const ModelToWorldTransform& getTransform() const { return transform; }
	inline ModelToWorldTransform& getTransform() { return transform; }
protected:
	Entity(Engine* engine) : m_engine(engine) {}
private:
	std::vector<std::unique_ptr<Entity>> m_children;
	std::vector<std::unique_ptr<BaseComponent>> m_components;
	ModelToWorldTransform transform;
	Engine* m_engine;

	void setEngine(Engine* engine);
};



