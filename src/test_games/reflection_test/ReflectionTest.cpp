#include "ReflectionTest.hpp"

#include "../../components/camera/FPCameraComponent.hpp"
#include "../../components/MovableComponent.hpp"

ReflectionTest::ReflectionTest(Engine* engine) : Game(engine) {

	Mesh::meshManager.emplace("cube.obj");
	Mesh::meshManager.emplace("monkey3.obj");
	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");
	Texture::textureManager.emplace("cube_skybox");

	Material test(Texture::textureManager.getPointer("test.png"), nullptr, nullptr);
	Material mirror(nullptr, nullptr, nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);
	Material brick(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr,
				   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
	Material sky(Texture::textureManager.getPointer("cube_skybox"), nullptr, nullptr);

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	//Entity* plane = new Entity();
	//plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), test));
	//m_gameWorld.rootEntity.addChildEntity(plane);
	m_skybox.reset(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), sky));
	m_gameWorld.currentSkyBox = m_skybox.get();

	Entity* object = new Entity();
	object->getLocalTransform().translate(glm::vec3(0.0, 1.0, -3.0));
	object->addComponent(new RenderComponent(Mesh::meshManager.getPointer("monkey3.obj"), brick));
	m_gameWorld.rootEntity.addChildEntity(object);

	Entity* object2 = new Entity();
	object2->getLocalTransform().translate(glm::vec3(0.0, 1.0, 3.0));
	object2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("monkey3.obj"), mirror, Texture::textureManager.getPointer("cube_skybox")));
	object2->addComponent(new MovableComponent());
	m_gameWorld.rootEntity.addChildEntity(object2);

}
