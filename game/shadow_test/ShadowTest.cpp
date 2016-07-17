#include "ShadowTest.hpp"

#include "../../src/components/camera/FPCameraComponent.hpp"
#include "../../src/components/MovableComponent.hpp"
#include "../../src/components/RotationComponent.hpp"

void ShadowTest::addCube(Entity& root, const Material& material, const glm::vec3& position, const glm::vec3& scale) {
	Entity* cube = new Entity();
	cube->getLocalTransform().translate(position);
	cube->getLocalTransform().scale(scale);
	cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), material));
	cube->addComponent(new MovableComponent());
	root.addChildEntity(cube);
}

ShadowTest::ShadowTest() {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");

	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr,
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

	Model modelPlane;
	modelPlane.makePlane(ROOM_WIDTH, ROOM_WIDTH, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Model modelPlane2;
	modelPlane2.makePlane(ROOM_WIDTH, ROOM_HEIGHT, 1);
	modelPlane2.finalize();
	Mesh::meshManager.emplace("planeSmall", modelPlane2);
	Mesh::meshManager.emplace("cube.obj");
	Mesh::meshManager.emplace("monkey3.obj");

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 10.0f));
	camera->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, ROOM_WIDTH / 2.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;
	Entity* playerModel = new Entity();
	playerModel->addComponent(new RenderComponent(Mesh::meshManager.getPointer("monkey3.obj"), checkers));
	playerModel->getLocalTransform().setScale(glm::vec3(0.1, 0.1, 0.1));
	playerModel->getLocalTransform().translate(glm::vec3(0.0, 0.0, 0.1));
	playerModel->getLocalTransform().rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	camera->addChildEntity(playerModel);

	Entity* floor = new Entity();
	floor->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(floor);

	Entity* ceiling = new Entity();
	ceiling->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	ceiling->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT, 0.0f));
	ceiling->getLocalTransform().rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(ceiling);

	Entity* wall1 = new Entity();
	wall1->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), checkers));
	wall1->getLocalTransform().translate(glm::vec3(ROOM_WIDTH / 2.0f, ROOM_HEIGHT / 2.0f, 0.0f));
	wall1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	wall1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall1);

	Entity* wall2 = new Entity();
	wall2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), checkers));
	wall2->getLocalTransform().translate(glm::vec3(-ROOM_WIDTH / 2.0f, ROOM_HEIGHT / 2.0f, 0.0f));
	wall2->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	wall2->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall2);

	Entity* wall3 = new Entity();
	wall3->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), checkers));
	wall3->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, ROOM_WIDTH / 2.0f));
	wall3->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall3);

	Entity* wall4 = new Entity();
	wall4->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), checkers));
	wall4->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, -ROOM_WIDTH / 2.0f));
	wall4->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall4);

	Entity* spotLight = new Entity();
	spotLight->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, 0.0f));
	spotLight->addComponent(new SpotLightComponent(glm::vec3(1.0, 1.0, 1.0), 1.5f, 10.0f, 0.6f, Attenuation(0.44, 0.35, 1.0), false));
	//pointLight->addComponent(new MovableComponent());
	spotLight->addComponent(new RotationComponent(-0.8f, glm::vec3(0.0, 1.0, 0.0)));
	m_gameWorld.rootEntity.addChildEntity(spotLight);

	addCube(m_gameWorld.rootEntity, bricks, glm::vec3(ROOM_WIDTH / 4.0f, ROOM_HEIGHT / 2.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	m_gameWorld.ambientLight = glm::vec3(0.05, 0.05, 0.05);
}
