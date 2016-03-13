#pragma once

#include "BaseComponent.hpp"

#include "../rendering/model/Mesh.hpp"
#include "../rendering/Material.hpp"

#include <iostream>

class RenderComponent : public BaseComponent {
public:
	RenderComponent(const Mesh* mesh, const Material& material) : m_mesh(mesh), m_material(material) {}

	virtual void render(Shader& shader) const {
		shader.setMaterial(m_material);
		shader.setModelToWorldMatrix(getTransformationMatrix());
		m_mesh->draw();
	}
private:
	const Mesh* m_mesh;
	Material m_material;
};



