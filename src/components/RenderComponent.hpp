#pragma once

#include "BaseComponent.hpp"

#include "../rendering/model/Mesh.hpp"
#include "../rendering/Material.hpp"
#include "../rendering/texture/TextureCubeData.hpp"

class RenderComponent : public BaseComponent {
public:
	RenderComponent(const Mesh* mesh,
					const Material& material,
					const BaseTextureData* reflectionMap = nullptr)
			        : mesh(mesh),
					  material(material),
					  reflectionMap(reflectionMap) { }

	virtual void render(Shader& shader) const;

	const Mesh* mesh;
	Material material;
	const BaseTextureData* reflectionMap;
};



