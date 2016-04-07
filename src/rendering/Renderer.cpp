#include <iostream>
#include "Renderer.hpp"

//Renderer::Renderer(Window* window) : m_window(window), shadowBuffer(1024, 1024) {
Renderer::Renderer(Window* window) : m_window(window) {
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

void Renderer::render(GameWorld& gameWorld) {
	renderScene(gameWorld);
}

void Renderer::renderShadows(const GameWorld& gameWorld, const BaseCameraComponent& lightCamera, Shader& shader) {
	glClear(GL_DEPTH_BUFFER_BIT);
	shader.useShader();
	shader.setCamera(lightCamera);
	gameWorld.rootEntity.render(shader);
}

void Renderer::renderScene(const GameWorld& gameWorld) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_window->bindAsRenderTarget();
	renderSkybox(gameWorld);
	m_ambientLightShader.useShader();
	m_ambientLightShader.setCamera(*gameWorld.currentCamera);
	m_ambientLightShader.setAmbientLight(gameWorld.ambientLight);
	gameWorld.rootEntity.render(m_ambientLightShader);

	for (auto l : m_directionalLights) {
		if (!l->isXray()) {
			disableBlending();
			l->getShadowMapBuffer()->bind();
			renderShadows(gameWorld, *l->getCamera(), m_shadowShader);
		}
		enableBlending();
		m_window->bindAsRenderTarget();
		m_directionalLightShader.useShader();
		m_directionalLightShader.setCamera(*gameWorld.currentCamera);
		m_directionalLightShader.setDirectionalLight(*l);
		gameWorld.rootEntity.render(m_directionalLightShader);
	}


	for (auto l : m_pointLights) {
		if (!l->isXray()) {
			disableBlending();
			l->getShadowMapBuffer()->bind();
			renderShadows(gameWorld, *l->getCamera(), m_shadowCubeShader);
		}
		enableBlending();
		m_window->bindAsRenderTarget();
		m_pointLightShader.useShader();
		m_pointLightShader.setCamera(*gameWorld.currentCamera);
		m_pointLightShader.setPointLight(*l);
		gameWorld.rootEntity.render(m_pointLightShader);
	}

	for (auto l : m_spotLights) {
		if (!l->isXray()) {
			disableBlending();
			l->getShadowMapBuffer()->bind();
			renderShadows(gameWorld, *l->getCamera(), m_shadowShader);
		}
		enableBlending();
		m_window->bindAsRenderTarget();
		m_spotLightShader.useShader();
		m_spotLightShader.setCamera(*gameWorld.currentCamera);
		m_spotLightShader.setSpotLight(*l);
		gameWorld.rootEntity.render(m_spotLightShader);
	}

	disableBlending();
}

void Renderer::renderSkybox(const GameWorld& gameWorld) {
	if (gameWorld.currentSkyBox != nullptr) {
		glDepthMask(GL_FALSE);
		glFrontFace(GL_CW);
		m_skyboxShader.useShader();
		m_skyboxShader.setCamera(*gameWorld.currentCamera);
		m_skyboxShader.setAmbientLight(gameWorld.ambientLight);
		gameWorld.currentSkyBox->render(m_skyboxShader);
		glDepthMask(GL_TRUE);
		glFrontFace(GL_CCW);
	}
}

void Renderer::enableBlending() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
}

void Renderer::disableBlending() {
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
