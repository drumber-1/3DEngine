#pragma once

#include "Window.hpp"
#include "model/MeshList.hpp"
#include "texture/TextureList.hpp"
#include "../core/ModelToWorldTransform.hpp"
#include "Camera.hpp"
#include "CameraProjection.hpp"
#include "shader/BasicTextureShader.hpp"

class Renderer {
public:
	Renderer(const Window& window);
	virtual ~Renderer() {}

	void render(const Camera& camera);
private:
	const Window* m_window;

	MeshList m_meshes;
	TextureList m_textures;

	CameraProjection m_cameraProjection;
	ModelToWorldTransform m_testTransform;

	BasicTextureShader m_basicTextureShader;
};
