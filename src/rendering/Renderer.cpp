#include "Renderer.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "texture/TextureList.hpp"
#include "../core/Time.hpp"

Renderer::Renderer(const Window& window) : m_window(&window),
										   m_cameraProjection(70.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.01f, 10.0f),
										   m_testMaterial(TextureList::getAddTextureGlobal("test.png"), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f)),
										   m_testDLight(glm::vec3(1.0, 1.0, 1.0), 0.8f, glm::vec3(1.0, -0.2, 0.0)) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	m_meshes.add("cube.obj");
	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	m_meshes.add("plane", modelPlane);

	//m_basicTextureShader.useShader();
	m_phongShader.useShader();
	m_phongShader.setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	m_phongShader.setDirectiobalLight(m_testDLight);
}

void Renderer::render(const Camera& camera) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_phongShader.setEyePositionWorld(camera.getPosition());

	//m_testDLight.setDirection(camera.getViewDirection());
	//m_phongShader.setDirectiobalLight(m_testDLight);

	m_testTransform.setTranslation(glm::vec3(0.0f, 1.1f, 3.0f));
	m_phongShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_phongShader.setModelToWorldMatrix(m_testTransform.getTransformationMatrix());
	m_phongShader.setMaterial(m_testMaterial);
	m_meshes.draw("cube.obj");

	m_testTransform.setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_phongShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_phongShader.setModelToWorldMatrix(m_testTransform.getTransformationMatrix());
	m_phongShader.setMaterial(m_testMaterial);
	m_meshes.draw("plane");

	Time::sleep(1);
}
