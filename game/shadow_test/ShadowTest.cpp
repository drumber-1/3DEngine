#include "ShadowTest.hpp"

#include "../../src/components/camera/FPCameraComponent.hpp"
#include "../../src/components/MovableComponent.hpp"
#include "../../src/components/RotationComponent.hpp"
#include "../../src/components/OrbitComponent.hpp"

void ShadowTest::addObject(Entity& root, const std::string& model, const Material& material, const glm::vec3& position, const glm::vec3& scale, bool orbit = false) {
	Entity* object = new Entity();
	object->getLocalTransform().translate(position);
	object->getLocalTransform().scale(scale);
	object->addComponent(new RenderComponent(Mesh::meshManager.getPointer(model), material));
	object->addComponent(new RotationComponent(0.4f, glm::vec3(0, 1, 0)));
	if (orbit) {
		object->addComponent(new OrbitComponent(position, glm::vec3(0, 1, 0), 0.8f, 0.5f));
	}
	root.addChildEntity(object);
}

ShadowTest::ShadowTest() {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");

	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

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
	camera->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 8.0f, ROOM_WIDTH / 4.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* floor = new Entity();
	floor->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(floor);

	Entity* light = new Entity();
	light->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f));
	light->getLocalTransform().setRotation(glm::radians(-45.0f), glm::vec3(1.0, 0.0, 0.0));
	m_gameWorld.rootEntity.addChildEntity(light);

	addObject(m_gameWorld.rootEntity, "cube.obj", bricks, glm::vec3(ROOM_WIDTH / 8.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	addObject(m_gameWorld.rootEntity, "cube.obj", checkers, glm::vec3(ROOM_WIDTH / 8.0f, 1.25f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), true);

	addObject(m_gameWorld.rootEntity, "monkey3.obj", bricks, glm::vec3(-ROOM_WIDTH / 8.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	m_gameWorld.ambientLight = glm::vec3(0.05, 0.05, 0.05);
}
