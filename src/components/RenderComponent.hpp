#pragma once

#include "BaseComponent.hpp"

#include "../rendering/model/Mesh.hpp"
#include "../rendering/Material.hpp"

class RenderComponent : public BaseComponent {
public:
	RenderComponent(const Mesh* mesh, const Material& material) : mesh(mesh), material(material) {}
	virtual void render(Shader& shader) const;
	const Mesh* mesh;
	Material material;
};



