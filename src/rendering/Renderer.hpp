#pragma once

#include "Window.hpp"
#include "model/MeshList.hpp"
#include "texture/TextureList.hpp"
#include "../core/ModelToWorldTransform.hpp"
#include "Camera.hpp"
#include "CameraProjection.hpp"
#include "shader/BasicTextureShader.hpp"
#include "Material.hpp"
#include "shader/PhongShader.hpp"

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(const Camera& camera);
private:
	const Window* m_window;

	MeshList m_meshes;

	CameraProjection m_cameraProjection;

	ModelToWorldTransform m_testTransform;
	Material m_testMaterial;
	Material m_testMaterial2;

	BasicTextureShader m_basicTextureShader;
	PhongShader m_phongShader;

	DirectionalLight m_testDLight;
	PointLight m_testPLight;
	SpotLight m_testSLight;
};
