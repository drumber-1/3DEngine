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
	modelPlane.makePlane(100, 100, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Mesh::meshManager.emplace("cube.obj");

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 3.0f, 3.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(plane);

	//Entity* skyLight1 = new Entity();
	//skyLight1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	//skyLight1->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	//skyLight1->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.6f, false));
	//m_gameWorld.rootEntity.addChildEntity(skyLight1);

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

	m_gameWorld.ambientLight = glm::vec3(0.2, 0.2, 0.2);
}
