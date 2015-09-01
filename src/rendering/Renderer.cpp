#include "Renderer.hpp"

#include <GL/glew.h>

#include "Window.hpp"
#include "../core/Time.hpp"

Renderer::Renderer(const Window& window) : m_window(&window),
										   m_cameraProjection(70.0f, (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 10.0f),
										   m_testShader("res/shaders/test_vert.glsl", "res/shaders/test_frag.glsl") {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	/*Model testModel;
	testModel.addVertex(-1.0f, -1.0f, +0.0f);
	testModel.addVertex(+0.0f, +1.0f, +0.0f);
	testModel.addVertex(+1.0f, -1.0f, +0.0f);
	testModel.addVertex(+0.0f, -1.0f, +1.0f);
	testModel.addTri(0, 1, 3);
	testModel.addTri(3, 1, 2);
	testModel.addTri(2, 1, 0);
	testModel.addTri(0, 2, 3);
	testModel.finalize();
	m_testMesh.load(testModel);*/

	m_meshes.add("cube.obj", "res/models/cube.obj");
	//m_testMesh.load("res/models/cube.obj");

	m_textures.add("test.png", "res/textures/test.png");

	m_testShader.useShader();
	//m_testShader.addUniform("modelToWorldMatrix");
	m_testShader.addUniform("modelToProjectionMatrix");
}

void Renderer::render(const Camera& camera) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_testTransform.setTranslation(glm::vec3(0.0f, 0.0f, 3.0f));
//
//	m_testTransform.setTranslation(glm::vec3(-1 * (m_window->getInput().getMousePositionX() / 400.0f - 1), -1 *(m_window->getInput().getMousePositionY() / 300.0f - 1), 5.0f));
//	m_testTransform.rotate(m_window->getInput().getMouseWheel() / 10.0f, glm::vec3(0, 1, 0));
//	if (m_window->getInput().getMousePressedLast(SDL_BUTTON_LEFT)) {
//		m_testTransform.scale(glm::vec3(1.1f, 1.1f, 1.1f));
//	}
//
//	if (m_window->getInput().getMousePressedLast(SDL_BUTTON_RIGHT)) {
//		m_testTransform.scale(glm::vec3(0.9f, 0.9f, 0.9f));
//	}

	//m_testShader.setUniform("modelToWorldMatrix", m_testTransform.getTransformationMatrix());
	m_testShader.setUniform("modelToProjectionMatrix", m_cameraProjection.getViewToProjection() * camera.getWorldToViewMatrix() * m_testTransform.getTransformationMatrix());
	m_textures.bind("test.png");
	m_meshes.draw("cube.obj");
	//m_testTexture.bind();
	//m_testMesh.draw();
	Time::sleep(1);
}