#include "Renderer.hpp"
#include "texture/Texture.hpp"

Renderer::Renderer(Window* window) : m_window(window),
									 m_ambientLight(0.1f, 0.1f, 0.1f) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	m_ambientLightShader.useShader();

	//Load some default textures
	Texture::textureManager.emplace("default_normal.jpg");
	Texture::textureManager.emplace("default_spec.png");
}

void Renderer::render(const CameraComponent& camera, const Entity& root) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ambientLightShader.useShader();
	m_ambientLightShader.setCamera(camera);
	m_ambientLightShader.setAmbientLight(m_ambientLight);
	root.render(m_ambientLightShader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	m_directionalLightShader.useShader();
	m_directionalLightShader.setCamera(camera);
	for (auto l : m_directionalLights) {
		m_directionalLightShader.setDirectionalLight(*l);
		root.render(m_directionalLightShader);
	}


	m_pointLightShader.useShader();
	m_pointLightShader.setCamera(camera);
	for (auto l : m_pointLights) {
		m_pointLightShader.setPointLight(*l);
		root.render(m_pointLightShader);
	}

	m_spotLightShader.useShader();
	m_spotLightShader.setCamera(camera);
	for (auto l : m_spotLights) {
		m_spotLightShader.setSpotLight(*l);
		root.render(m_spotLightShader);
	}

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
