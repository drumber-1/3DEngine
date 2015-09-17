#include "Renderer.hpp"

#include "texture/Texture.hpp"
#include "model/Mesh.hpp"

ResourceManager<Mesh> Renderer::meshManager;
ResourceManager<Texture> Renderer::textureManager;

Renderer::Renderer(Window* window) : m_window(window),
									 m_ambientLight(0.2f, 0.2f, 0.2f) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	//m_phongShader.useShader();
	m_ambientLightShader.useShader();
}

void Renderer::render(const Camera& camera, const Entity& root) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//m_phongShader.setAmbientLight(m_ambientLight);
	//m_phongShader.setEyePositionWorld(camera.getPosition());
	//m_phongShader.setWorldToProjectionMatrix(camera.getWorldToProjectionMatrix());
	//root.render(m_phongShader);
	m_ambientLightShader.setAmbientLight(m_ambientLight);
	m_ambientLightShader.setCamera(camera);
	root.render(m_ambientLightShader);
}
