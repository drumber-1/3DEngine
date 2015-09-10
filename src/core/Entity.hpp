#pragma once

#include <memory>
#include <vector>

#include "Input.hpp"
#include "../rendering/Renderer.hpp"

class BaseComponent;

class Entity {
public:
	void update(const Input& input, float delta);
	void render(const Renderer& renderer, const PhongShader& shader);

	void addChildEntity(std::unique_ptr<Entity>& entity);
	void addChildEntity(Entity* entity);

	void addComponent(std::unique_ptr<BaseComponent>& baseComponent);
	void addComponent(BaseComponent* baseComponent);

	inline const ModelToWorldTransform& getTransform() const { return transform; }
	inline ModelToWorldTransform& getTransform() { return transform; }
private:
	std::vector<std::unique_ptr<Entity>> m_children;
	std::vector<std::unique_ptr<BaseComponent>> m_components;
	ModelToWorldTransform transform;
};



