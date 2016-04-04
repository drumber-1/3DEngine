#include "ShadowTest.hpp"

#include "../../components/camera/FPCameraComponent.hpp"
#include "../../components/MovableComponent.hpp"

void ShadowTest::addCube(Entity& root, const Material& material, const glm::vec3& position, const glm::vec3& scale) {
	Entity* cube = new Entity();
	cube->getLocalTransform().translate(position);
	cube->getLocalTransform().scale(scale);
	cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), material));
	cube->addComponent(new MovableComponent());
	root.addChildEntity(cube);
}

ShadowTest::ShadowTest(Engine* engine) : Game(engine) {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");

	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0,
					Texture::textureManager.getPointer("bricks_normal.jpg"));

	Model modelPlane;
	modelPlane.makePlane(ROOM_WIDTH, ROOM_WIDTH, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Model modelPlane2;
	modelPlane2.makePlane(ROOM_WIDTH, ROOM_HEIGHT, 1);
	modelPlane2.finalize();
	Mesh::meshManager.emplace("planeSmall", modelPlane2);
	Mesh::meshManager.emplace("cube.obj");

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, ROOM_WIDTH / 4.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* floor = new Entity();
	floor->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(floor);

	Entity* ceiling = new Entity();
	ceiling->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	ceiling->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT, 0.0f));
	ceiling->getLocalTransform().rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(ceiling);

	Entity* wall1 = new Entity();
	wall1->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), bricks));
	wall1->getLocalTransform().translate(glm::vec3(ROOM_WIDTH / 2.0f, ROOM_HEIGHT / 2.0f, 0.0f));
	wall1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	wall1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall1);

	Entity* wall2 = new Entity();
	wall2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), bricks));
	wall2->getLocalTransform().translate(glm::vec3(-ROOM_WIDTH / 2.0f, ROOM_HEIGHT / 2.0f, 0.0f));
	wall2->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	wall2->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall2);

	Entity* wall3 = new Entity();
	wall3->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), bricks));
	wall3->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, ROOM_WIDTH / 2.0f));
	wall3->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall3);

	Entity* wall4 = new Entity();
	wall4->addComponent(new RenderComponent(Mesh::meshManager.getPointer("planeSmall"), bricks));
	wall4->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, -ROOM_WIDTH / 2.0f));
	wall4->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(wall4);

	Entity* skyLight1 = new Entity();
	skyLight1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight1->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight1->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.6f, false));
	m_gameWorld.rootEntity.addChildEntity(skyLight1);

	//Entity* skyLight2 = new Entity();
	//skyLight2->getLocalTransform().rotate(glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
	//skyLight2->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	//skyLight2->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.6f, false));
	//m_gameWorld.rootEntity.addChildEntity(skyLight2);

	Entity* pointLight = new Entity();
	pointLight->getLocalTransform().translate(glm::vec3(0.0f, 3.0f, 0.0f));
	pointLight->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
	pointLight->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 1.5f, 10.0f, false));
	m_gameWorld.rootEntity.addChildEntity(pointLight);

	addCube(m_gameWorld.rootEntity, bricks, glm::vec3(0.0f, 1.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	//Entity* cube = new Entity();
	//cube->getLocalTransform().translate(glm::vec3(0.0f, 2.7f, 0.0f));
	//cube->getLocalTransform().scale(glm::vec3(0.1f, 0.1f, 0.1f));
	//cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), bricks));
	//cube->addComponent(new RotationComponent(0.2f, glm::vec3(1.0f, 0.0f, 0.0f)));
	//m_gameWorld.rootEntity.addChildEntity(cube);

	m_gameWorld.ambientLight = glm::vec3(0.5, 0.5, 0.5);
}
