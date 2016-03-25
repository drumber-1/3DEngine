#include "ShadowTest.hpp"

#include "../../components/camera/FPCameraComponent.hpp"
#include "../../components/RotationComponent.hpp"

void ShadowTest::addCube(Entity& root, const Material& material, const glm::vec3& position) {
	Entity* cube = new Entity();
	cube->getLocalTransform().translate(position);
	cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), material));
	cube->addComponent(new RotationComponent(0.3f, glm::vec3(0.0f, 1.0f, 0.0f)));
	root.addChildEntity(cube);
}

ShadowTest::ShadowTest(Engine* engine) : Game(engine) {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");

	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0, Texture::textureManager.getPointer("bricks_normal.jpg"));

	Model modelPlane;
	modelPlane.makePlane(100, 100, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Mesh::meshManager.emplace("cube.obj");

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	//Entity* cameraLight = new Entity();
	//cameraLight->addComponent(new SpotLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100, 0.8f));
	//camera->addChildEntity(cameraLight);

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(plane);

	Entity* skyLight = new Entity();
	//skyLight->getLocalTransform().translate(glm::vec3(0.0f, 10.0f, 0.0f));
	skyLight->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	//skyLight->getLocalTransform().rotate(glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f));
	m_gameWorld.rootEntity.addChildEntity(skyLight);

	addCube(m_gameWorld.rootEntity, bricks, glm::vec3(0.0f, 2.1f, 0.0f));

	m_gameWorld.ambientLight = glm::vec3(0.2, 0.2, 0.2);
}
