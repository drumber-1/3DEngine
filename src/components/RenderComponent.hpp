#pragma once

class RenderComponent : public BaseComponent {
public:
	RenderComponent(const Mesh* mesh, const Material material) : m_mesh(mesh), m_material(material) {}

	virtual void render(const Renderer& renderer) const {

	}
private:
	const Mesh* m_mesh;
	Material m_material;
};



