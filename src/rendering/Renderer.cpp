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
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthFunc(GL_LESS);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);


	m_ambientLightShader.useShader();

	//Load some default textures
	Texture::textureManager.emplace("default_diff.png");
	Texture::textureManager.emplace("default_normal.jpg");
	Texture::textureManager.emplace("default_spec.png");
}

void Renderer::render(GameWorld& gameWorld) {
	//Render shadowmaps first
	for (auto& l : gameWorld.m_directionalLights) {
		if (!l->isXray()) {
			renderShadows(gameWorld, l, m_shadowShader);
		}
	}

	for (auto& l : gameWorld.m_pointLights) {
		if (!l->isXray()) {
			renderShadows(gameWorld, l, m_shadowCubeShader);
		}
	}

	for (auto& l : gameWorld.m_spotLights) {
		if (!l->isXray()) {
			renderShadows(gameWorld, l, m_shadowShader);
		}
	}

	for (auto& rt : gameWorld.m_renderTargets) {
		if (rt.shouldRender()) {
			for (int i = 0; i < 6; ++i) {
				rt.bindAsRenderTarget(i);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				renderScene(gameWorld, rt.getCamera());
			}
		}
	}

	m_window->bindAsRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderScene(gameWorld, gameWorld.currentCamera);
}

void Renderer::renderShadows(const GameWorld& gameWorld, const BaseLightComponent* light, Shader& shader) {
	light->getShadowMapBuffer()->bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	disableBlending();
	shader.useShader();
	shader.setCamera(*(light->getCamera()));
	gameWorld.rootEntity.render(shader);
}

void Renderer::renderScene(const GameWorld& gameWorld, const BaseCameraComponent* camera) {
	m_ambientLightShader.useShader();
	m_ambientLightShader.setCamera(*camera);
	m_ambientLightShader.setAmbientLight(gameWorld.ambientLight);
	gameWorld.rootEntity.render(m_ambientLightShader);

	enableBlending();

	glBlendFunc(GL_ONE, GL_ONE);

	for (auto l : gameWorld.m_directionalLights) {
		m_directionalLightShader.useShader();
		m_directionalLightShader.setCamera(*camera);
		m_directionalLightShader.setDirectionalLight(*l);
		gameWorld.rootEntity.render(m_directionalLightShader);
	}

	for (auto l : gameWorld.m_pointLights) {
		m_pointLightShader.useShader();
		m_pointLightShader.setCamera(*camera);
		m_pointLightShader.setPointLight(*l);
		gameWorld.rootEntity.render(m_pointLightShader);
	}

	for (auto l : gameWorld.m_spotLights) {
		m_spotLightShader.useShader();
		m_spotLightShader.setCamera(*camera);
		m_spotLightShader.setSpotLight(*l);
		gameWorld.rootEntity.render(m_spotLightShader);
	}

	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	m_reflectionShader.useShader();
	m_reflectionShader.setCamera(*camera);
	gameWorld.rootEntity.render(m_reflectionShader);
	glBlendFunc(GL_ONE, GL_ONE);

	if (gameWorld.currentSkyBox != nullptr) {
		glDepthFunc(GL_LEQUAL);
		glFrontFace(GL_CW);
		m_skyboxShader.useShader();
		m_skyboxShader.setCamera(*camera);
		m_skyboxShader.setAmbientLight(gameWorld.ambientLight);
		gameWorld.currentSkyBox->render(m_skyboxShader);
		glDepthFunc(GL_LESS);
		glFrontFace(GL_CCW);
	}

	disableBlending();
}

void Renderer::enableBlending() {
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);
}

void Renderer::disableBlending() {
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}
