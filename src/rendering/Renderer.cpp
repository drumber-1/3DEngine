#include <iostream>
#include "Renderer.hpp"
#include "../components/camera/OrthographicCameraComponent.hpp"

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

void Renderer::renderShadows(const GameWorld& gameWorld, const BaseCameraComponent& lightCamera) {
	glClear(GL_DEPTH_BUFFER_BIT);
	m_shadowShader.useShader();
	m_shadowShader.setCamera(lightCamera);
	gameWorld.rootEntity.render(m_shadowShader);
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

		disableBlending();

		l->getShadowMapBuffer()->bind();
		renderShadows(gameWorld, *l->getCamera());

		enableBlending();

		m_window->bindAsRenderTarget();
		m_directionalLightShader.useShader();
		m_directionalLightShader.setCamera(*gameWorld.currentCamera);
		m_directionalLightShader.setUniform("shadowMap", &(l->getShadowMapBuffer()->getShadowMap()));

		m_directionalLightShader.setUniform("lightSpaceMatrix", l->getCamera()->getWorldToProjectionMatrix());
		m_directionalLightShader.setDirectionalLight(*l);
		gameWorld.rootEntity.render(m_directionalLightShader);
	}


	m_pointLightShader.useShader();
	m_pointLightShader.setCamera(*gameWorld.currentCamera);
	for (auto l : m_pointLights) {
		m_pointLightShader.setPointLight(*l);
		gameWorld.rootEntity.render(m_pointLightShader);
	}

	m_spotLightShader.useShader();
	m_spotLightShader.setCamera(*gameWorld.currentCamera);
	for (auto l : m_spotLights) {
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
