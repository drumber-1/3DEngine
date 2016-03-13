#include "TestGame.hpp"

#include "../components/RenderComponent.hpp"
#include "../components/FPCameraComponent.hpp"
#include "../components/MovableComponent.hpp"
#include "../components/RotationComponent.hpp"

TestGame::TestGame(Engine* engine) : Game(engine) {
	Entity* camera = new Entity();
	CameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_rootEntity.addChildEntity(camera);
	m_currentCamera = cameraComponent;

	Entity* cameraLight = new Entity();
	cameraLight->addComponent(new SpotLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100, 0.8f));
	camera->addChildEntity(cameraLight);

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
	monkey->getLocalTransform().translate(glm::vec3(-1.0f, 1.1f, -3.0f));
	monkey->addComponent(new RenderComponent(Renderer::meshManager.getPointer("monkey3.obj"), checkers));
	monkey->addComponent(new MovableComponent());
	m_rootEntity.addChildEntity(monkey);
	Entity* monkeyLight = new Entity();
	monkeyLight->addComponent(new PointLightComponent(glm::vec3(1.0, 0.0, 0.0), 0.4f, 5));
	monkeyLight->getLocalTransform().translate(glm::vec3(0.0f, -1.0f, 0.0f));
	monkey->addChildEntity(monkeyLight);
	Entity* monkeyCube = new Entity();
	monkeyCube->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	monkeyCube->getLocalTransform().scale(glm::vec3(0.1f, 0.1f, 0.1f));
	monkeyCube->addComponent(new RenderComponent(Renderer::meshManager.getPointer("cube.obj"), brick));
	monkey->addChildEntity(monkeyCube);

	Entity* cube = new Entity();
	cube->getLocalTransform().translate(glm::vec3(1.0f, 1.1f, 3.0f));
	cube->addComponent(new RenderComponent(Renderer::meshManager.getPointer("cube.obj"), brick));
	cube->addComponent(new RotationComponent(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_rootEntity.addChildEntity(cube);

	Entity* cubeLight = new Entity();
	cubeLight->addComponent(new SpotLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.4f, 10, 0.8f));
	cubeLight->getLocalTransform().translate(glm::vec3(1.0f, 0.1f, 1.2f));
	cubeLight->getLocalTransform().rotate(glm::radians(135.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_rootEntity.addChildEntity(cubeLight);

	Entity* skyLight = new Entity();
	skyLight->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight->addComponent(new DirectionalLightComponent(glm::vec3(0.2, 0.4, 0.6), 0.4f));
	m_rootEntity.addChildEntity(skyLight);
}

