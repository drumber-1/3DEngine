#include "Showcase.hpp"

#include "../../src/components/camera/FPCameraComponent.hpp"
#include "../../src/components/MovableComponent.hpp"
#include "../../src/components/PendulumComponent.hpp"

void Showcase::addCube(Entity& root, const Material& material, const glm::vec3& position, const glm::vec3& scale) {
	Entity* cube = new Entity();
	cube->getLocalTransform().translate(position);
	cube->getLocalTransform().scale(scale);
	cube->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), material));
	cube->addComponent(new MovableComponent());
	root.addChildEntity(cube);
}

Showcase::Showcase() {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");
	Texture::textureManager.emplace("cube_skybox");

	Material white(Texture::textureManager.getPointer("default_diff.png"));
	Material checkers(Texture::textureManager.getPointer("test.png"));
	Material bricks(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr,
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
	Material mirror(nullptr, nullptr, nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);
	Material sky(Texture::textureManager.getPointer("cube_skybox"));

	Model modelPlane;
	modelPlane.makePlane(ROOM_WIDTH, ROOM_WIDTH, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Model modelPlane2;
	modelPlane2.makePlane(ROOM_WIDTH, ROOM_HEIGHT, 1);
	modelPlane2.finalize();
	Mesh::meshManager.emplace("planeSmall", modelPlane2);
	Mesh::meshManager.emplace("cube.obj");
	Mesh::meshManager.emplace("sphere.obj");
	Mesh::meshManager.emplace("monkey3.obj");
	Mesh::meshManager.emplace("lampshade.obj");

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 10.0f));
	camera->getLocalTransform().translate(glm::vec3(0.0f, ROOM_HEIGHT / 2.0f, ROOM_WIDTH));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* floor = new Entity();
	floor->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), checkers));
	m_gameWorld.rootEntity.addChildEntity(floor);

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

	Entity* lamp = new Entity();
	lamp->getLocalTransform().scale(glm::vec3(0.4, 0.4, 0.4));
	lamp->addComponent(new PendulumComponent(glm::vec3(0.0, ROOM_HEIGHT, 0.0), glm::vec3(0.0, ROOM_HEIGHT - 1.0, 0.0), glm::vec3(1.0, 0.0, 0.0), 7.0, glm::radians(45.0f)));
	lamp->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 10.0f, Attenuation(0.2, 0.8, 0.0), false));
	lamp->addComponent(new RenderComponent(Mesh::meshManager.getPointer("lampshade.obj"), white));
	m_gameWorld.rootEntity.addChildEntity(lamp);

	Entity* sphere = new Entity();
	sphere->getLocalTransform().translate(glm::vec3(ROOM_WIDTH / 4.0f, ROOM_HEIGHT / 4.0f, ROOM_WIDTH / 4.0f));
	sphere->getLocalTransform().scale(glm::vec3(0.8, 0.8, 0.8));
	CubeCameraComponent* reflectCam = new CubeCameraComponent(90, 1.0);
	sphere->addComponent(reflectCam);
	m_gameWorld.m_renderTargets.emplace_back(512, 512, reflectCam, 1);
	sphere->addComponent(new RenderComponent(Mesh::meshManager.getPointer("sphere.obj"), mirror, m_gameWorld.m_renderTargets[0].getTextureData()));
	m_gameWorld.rootEntity.addChildEntity(sphere);

	m_gameWorld.ambientLight = glm::vec3(0.2, 0.2, 0.2);
	m_skybox.reset(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), sky));
	m_gameWorld.currentSkyBox = m_skybox.get();
}
