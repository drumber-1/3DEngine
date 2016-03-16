#include "NormalTest.hpp"

#include "../../components/RenderComponent.hpp"
#include "../../components/FPCameraComponent.hpp"
#include "../../components/MovableComponent.hpp"

void addCube(Entity& root, const Material& material, const glm::vec3& position) {
	Entity* cube = new Entity();
	cube->getLocalTransform().translate(position);
	cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), material));
	root.addChildEntity(cube);
}

NormalTest::NormalTest(Engine* engine) : Game(engine) {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");
	Texture::textureManager.emplace("snow_grass_d.jpg");
	Texture::textureManager.emplace("snow_grass_n.jpg");
	Texture::textureManager.emplace("snow_grass_s.jpg");

	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Material bricks_n(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0, Texture::textureManager.getPointer("bricks_normal.jpg"));
	Material snow_grass(Texture::textureManager.getPointer("snow_grass_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Material snow_grass_n(Texture::textureManager.getPointer("snow_grass_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("snow_grass_n.jpg"));
	Material snow_grass_ns(Texture::textureManager.getPointer("snow_grass_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("snow_grass_n.jpg"), Texture::textureManager.getPointer("snow_grass_s.jpg"));

	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Mesh::meshManager.emplace("cube.obj");

	Entity* camera = new Entity();
	CameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* cameraLight = new Entity();
	cameraLight->addComponent(new SpotLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100, 0.8f));
	camera->addChildEntity(cameraLight);

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(plane);

	Entity* skyLight = new Entity();
	skyLight->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight->addComponent(new DirectionalLightComponent(glm::vec3(0.2, 0.4, 0.6), 0.4f));
	m_gameWorld.rootEntity.addChildEntity(skyLight);

	Entity* probe = new Entity();
	probe->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, -0.5f));
	probe->getLocalTransform().scale(glm::vec3(0.1f, 0.1f, 0.1f));
	probe->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), checkers));
	probe->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100));
	probe->addComponent(new MovableComponent());
	m_gameWorld.rootEntity.addChildEntity(probe);

	addCube(m_gameWorld.rootEntity, bricks, glm::vec3(-1.0f, 1.1f, -3.0f));
	addCube(m_gameWorld.rootEntity, bricks_n, glm::vec3(1.0f, 1.1f, -3.0f));
	addCube(m_gameWorld.rootEntity, snow_grass, glm::vec3(-2.0f, 1.1f, -5.0f));
	addCube(m_gameWorld.rootEntity, snow_grass_n, glm::vec3(0.0f, 1.1f, -5.0f));
	addCube(m_gameWorld.rootEntity, snow_grass_ns, glm::vec3(2.0f, 1.1f, -5.0f));
}
