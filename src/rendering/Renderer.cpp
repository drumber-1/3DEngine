#include "Renderer.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "../core/Time.hpp"

Renderer::Renderer(const Window& window) : m_window(&window),
										   m_cameraProjection(70.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 10.0f),
										   m_testMaterial("test.png", glm::vec4(1.0f, 1.0f, 1.0f, 0.5f)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	m_meshes.add("cube.obj");
	m_textures.add("test.png");

	m_basicTextureShader.useShader();
}

void Renderer::render(const Camera& camera) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_testTransform.setTranslation(glm::vec3(0.0f, 0.0f, 3.0f));
	m_basicTextureShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_textures.bind("test.png");
	m_meshes.draw("cube.obj");

	Time::sleep(1);
}