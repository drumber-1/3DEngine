#include "Renderer.hpp"
#include "texture/Texture.hpp"
#include "../core/GameWorld.hpp"

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

void Renderer::render(const GameWorld& gameWorld) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderSkybox(gameWorld);

	m_ambientLightShader.useShader();
	m_ambientLightShader.setCamera(*gameWorld.currentCamera);
	m_ambientLightShader.setAmbientLight(gameWorld.ambientLight);
	gameWorld.rootEntity.render(m_ambientLightShader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

	m_directionalLightShader.useShader();
	m_directionalLightShader.setCamera(*gameWorld.currentCamera);
	for (auto l : m_directionalLights) {
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

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void Renderer::renderSkybox(const GameWorld& gameWorld) {
	if (gameWorld.currentSkyBox != nullptr) {
		glDepthMask(GL_FALSE);
		glFrontFace(GL_CW);
		m_skyboxShader.useShader();
		m_skyboxShader.setCamera(*gameWorld.currentCamera);
		m_skyboxShader.setAmbientLight(gameWorld.ambientLight);
		m_skyboxShader.setUniform("modColour", glm::vec4(1, 1, 1, 1));
		Texture::textureManager.getPointer("cube_skybox")->bind(GL_TEXTURE0);
		Mesh::meshManager.getPointer("cube.obj")->draw();
		//m_skyboxShader.draw(*gameWorld.currentSkyBox);
		glDepthMask(GL_TRUE);
		glFrontFace(GL_CCW);
	}
}