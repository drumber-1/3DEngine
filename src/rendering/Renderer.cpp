#include "Renderer.hpp"

#include "texture/Texture.hpp"
#include "model/Mesh.hpp"

ResourceManager<Mesh> Renderer::meshManager;
ResourceManager<Texture> Renderer::textureManager;

Renderer::Renderer(Window* window) : m_window(window),
									 m_ambientLight(0.2f, 0.2f, 0.2f),
									 m_testDLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, glm::vec3(1.0f, -0.1f, 0.0f)),
									 m_testPLight(glm::vec3(1.0, 1.0, 1.0), 0.4f, glm::vec3(-1.0f, 0.1f, -3.0f), 5),
									 m_testSLight(glm::vec3(1.0, 1.0, 1.0), 0.8f, glm::vec3(0.0, 1.0, 0.0), 5, glm::vec3(0.0, 0.0, 0.0), glm::cos(glm::radians(40.0f))) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	m_ambientLightShader.useShader();
}

void Renderer::render(const Camera& camera, const Entity& root) {
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
	m_directionalLightShader.setDirectionalLight(m_testDLight);
	root.render(m_directionalLightShader);

	m_pointLightShader.useShader();
	m_pointLightShader.setCamera(camera);
	m_pointLightShader.setPointLight(m_testPLight);
	root.render(m_pointLightShader);

	m_testSLight.setPosition(camera.getPosition());
	m_testSLight.setDirection(camera.getViewDirection());
	m_spotLightShader.useShader();
	m_spotLightShader.setCamera(camera);
	m_spotLightShader.setPointLight(m_testSLight);
	root.render(m_spotLightShader);

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
