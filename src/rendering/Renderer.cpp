#include "Renderer.hpp"

#include "texture/Texture.hpp"
#include "model/Mesh.hpp"

ResourceManager<Mesh> Renderer::meshManager;
ResourceManager<Texture> Renderer::textureManager;

Renderer::Renderer(Window* window) : m_window(window),
									 m_cameraProjection(90.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.01f, 10.0f) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	m_phongShader.useShader();
	m_phongShader.setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
}

void Renderer::render(const Camera& camera, const Entity& root) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_phongShader.setEyePositionWorld(camera.getPosition());
	m_phongShader.setWorldToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix());

	root.render(m_phongShader);
}
