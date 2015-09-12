#pragma once

#include "Window.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "CameraProjection.hpp"

#include "model/Mesh.hpp"

#include "shader/BasicTextureShader.hpp"
#include "shader/PhongShader.hpp"

#include "../core/ModelToWorldTransform.hpp"
#include "../core/ResourceManager.hpp"
#include "../core/Entity.hpp"

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(const Camera& camera, const Entity& root);
	static ResourceManager<Mesh> meshManager;
	static ResourceManager<Texture> textureManager;
private:
	const Window* m_window;

	CameraProjection m_cameraProjection;

	BasicTextureShader m_basicTextureShader;
	PhongShader m_phongShader;
};
