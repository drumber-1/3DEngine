#include "Renderer.hpp"
#include "../components/camera/OrthographicCameraComponent.hpp"

Renderer::Renderer(Window* window) : m_window(window) , depthMap(1024, 1024) {
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

	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap.getID(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	shadowCam = new OrthographicCameraComponent(-5, 5, -5, 5);
	shadowEntity.addComponent(shadowCam);
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
	renderSkybox(gameWorld);

	m_ambientLightShader.useShader();
	m_ambientLightShader.setCamera(*gameWorld.currentCamera);
	m_ambientLightShader.setAmbientLight(gameWorld.ambientLight);
	gameWorld.rootEntity.render(m_ambientLightShader);

	for (auto l : m_directionalLights) {

		disableBlending();

		glViewport(0, 0, 1024, 1024);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		shadowEntity.getLocalTransform().setRotation(l->getRotation());
		shadowEntity.getLocalTransform().setTranslation(l->getPosition());
		renderShadows(gameWorld, *shadowCam);

		enableBlending();

		m_window->bindAsRenderTarget();
		m_directionalLightShader.useShader();
		m_directionalLightShader.setCamera(*gameWorld.currentCamera);
		m_directionalLightShader.setUniform("shadowMap", &depthMap);

		m_directionalLightShader.setUniform("lightSpaceMatrix", shadowCam->getWorldToProjectionMatrix());
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
