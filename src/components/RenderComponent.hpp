#pragma once

class RenderComponent : public BaseComponent {
public:
	RenderComponent(const Mesh* mesh, const Material material) : m_mesh(mesh), m_material(material) {}

	virtual void render(const Renderer& renderer, const PhongShader& shader) const {
		shader.setMaterial(m_material);
		shader.setModelToWorldMatrix(getTransform());
		m_mesh->draw();
	}
private:
	const Mesh* m_mesh;
	Material m_material;
};



