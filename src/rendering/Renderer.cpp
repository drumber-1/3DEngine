#include "Renderer.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "../core/Time.hpp"

ResourceManager<Mesh> Renderer::meshManager;
ResourceManager<Texture> Renderer::textureManager;

Renderer::Renderer(Window* window) : m_window(window),
									 m_cameraProjection(90.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.01f, 10.0f),
								 	 m_testMaterial(Renderer::textureManager.getAddResource("test.png"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
									 m_testMaterial2(Renderer::textureManager.getAddResource("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0),
									 m_testDLight(glm::vec3(1.0, 1.0, 1.0), 0.1f, glm::vec3(1.0, -0.2, 0.0)),
									 m_testPLight(glm::vec3(1.0, 1.0, 1.0), 0.4f, glm::vec3(0.0f, 0.1f, -3.0f), 5),
									 m_testSLight(glm::vec3(1.0, 1.0, 1.0), 0.8f, glm::vec3(0.0, 1.0, 0.0), 5, glm::vec3(0.0, 0.0, 0.0), glm::cos(glm::radians(40.0f))) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	Renderer::meshManager.emplace("cube.obj");
	Renderer::meshManager.emplace("monkey3.obj");
	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	Renderer::meshManager.emplace("plane", modelPlane);

	//m_basicTextureShader.useShader();
	m_phongShader.useShader();
	m_phongShader.setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	m_phongShader.setDirectionalLight(m_testDLight, 0);
	m_phongShader.setPointLight(m_testPLight, 0);
	m_phongShader.setSpotLight(m_testSLight, 0);
}

void Renderer::render(const Camera& camera) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_phongShader.setEyePositionWorld(camera.getPosition());

	//m_testDLight.setDirection(camera.getViewDirection());
	//m_phongShader.setDirectiobalLight(m_testDLight);

	//m_testPLight.setPosition(camera.getPosition());
	//m_phongShader.setPointLight(m_testPLight, 0);

	m_testSLight.setPosition(camera.getPosition());
	m_testSLight.setDirection(camera.getViewDirection());
	m_phongShader.setSpotLight(m_testSLight, 0);

	m_testTransform.setTranslation(glm::vec3(0.0f, 1.1f, 3.0f));
	m_phongShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_phongShader.setModelToWorldMatrix(m_testTransform.getTransformationMatrix());
	m_phongShader.setMaterial(m_testMaterial2);
	meshManager.getResource("cube.obj").draw();

	m_testTransform.setTranslation(glm::vec3(0.0f, 1.1f, -3.0f));
	m_phongShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_phongShader.setModelToWorldMatrix(m_testTransform.getTransformationMatrix());
	m_phongShader.setMaterial(m_testMaterial);
	meshManager.getResource("monkey3.obj").draw();

	m_testTransform.setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
	m_phongShader.setModelToProjectionMatrix(m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_phongShader.setModelToWorldMatrix(m_testTransform.getTransformationMatrix());
	m_phongShader.setMaterial(m_testMaterial);
	meshManager.getResource("plane").draw();

	Time::sleep(1);
}
