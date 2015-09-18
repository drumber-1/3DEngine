#include "TestGame.hpp"

#include "../components/RenderComponent.hpp"
#include "../rendering/Renderer.hpp"

TestGame::TestGame() {
	Renderer::meshManager.emplace("cube.obj");
	Renderer::meshManager.emplace("monkey3.obj");
	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	Renderer::meshManager.emplace("plane", modelPlane);

	Renderer::textureManager.emplace("test.png");
	Renderer::textureManager.emplace("bricks.jpg");

	Material checkers(Renderer::textureManager.getPointer("test.png"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Material brick(Renderer::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Renderer::meshManager.getPointer("plane"), checkers));
	m_rootEntity.addChildEntity(plane);

	Entity* monkey = new Entity();
	monkey->getTransform().translate(glm::vec3(-1.0f, 1.1f, -3.0f));
	monkey->addComponent(new RenderComponent(Renderer::meshManager.getPointer("monkey3.obj"), checkers));
	m_rootEntity.addChildEntity(monkey);

	Entity* cube = new Entity();
	cube->getTransform().translate(glm::vec3(1.0f, 1.1f, 3.0f));
	cube->addComponent(new RenderComponent(Renderer::meshManager.getPointer("cube.obj"), brick));
	m_rootEntity.addChildEntity(cube);

	m_camera.moveUp(0.5f);
}

// TODO Add light components

// Old lighting code:
//	m_testDLight.setDirection(camera.getViewDirection());
//	m_phongShader.setDirectiobalLight(m_testDLight);
//
//	m_testPLight.setPosition(camera.getPosition());
//	m_phongShader.setPointLight(m_testPLight, 0);
//
//	m_testSLight.setPosition(camera.getPosition());
//	m_testSLight.setDirection(camera.getViewDirection());
//	m_phongShader.setSpotLight(m_testSLight, 0);
//
//
//m_phongShader.useShader();
//m_phongShader.setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
//m_phongShader.setDirectionalLight(m_testDLight, 0);
//m_phongShader.setPointLight(m_testPLight, 0);
//m_phongShader.setSpotLight(m_testSLight, 0);
//
//m_testDLight(glm::vec3(1.0, 1.0, 1.0), 0.1f, glm::vec3(1.0, -0.2, 0.0)),
//m_testPLight(glm::vec3(1.0, 1.0, 1.0), 0.4f, glm::vec3(0.0f, 0.1f, -3.0f), 5),
//m_testSLight(glm::vec3(1.0, 1.0, 1.0), 0.8f, glm::vec3(0.0, 1.0, 0.0), 5, glm::vec3(0.0, 0.0, 0.0), glm::cos(glm::radians(40.0f)))
