#include "ReflectionTest.hpp"

#include "../../components/camera/FPCameraComponent.hpp"
#include "../../components/MovableComponent.hpp"

ReflectionTest::ReflectionTest() {

	Mesh::meshManager.emplace("cube.obj");
	Mesh::meshManager.emplace("monkey3.obj");
	Mesh::meshManager.emplace("sphere.obj");
	Model modelPlane;
	modelPlane.makePlane(10, 10, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks_normal.jpg");
	Texture::textureManager.emplace("snow_grass_d.jpg");
	Texture::textureManager.emplace("snow_grass_n.jpg");
	Texture::textureManager.emplace("snow_grass_s.jpg");
	Texture::textureManager.emplace("cube_skybox");

	Material snow_grass_ns(Texture::textureManager.getPointer("snow_grass_d.jpg"), Texture::textureManager.getPointer("snow_grass_n.jpg"), Texture::textureManager.getPointer("snow_grass_s.jpg"));
	Material test(Texture::textureManager.getPointer("test.png"), nullptr, nullptr);

	Material mirror(nullptr, nullptr, nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);
	//Material mirror(Texture::textureManager.getPointer("test.png"), nullptr, nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);
//	Material mirror(Texture::textureManager.getPointer("bricks.jpg"),
//					Texture::textureManager.getPointer("bricks_normal.jpg"),
//					nullptr,
//					glm::vec4(1.0, 1.0, 1.0, 1.0), 0.8f, 32.0f, true);
	//Material mirror(Texture::textureManager.getPointer("snow_grass_d.jpg"),
	//				Texture::textureManager.getPointer("snow_grass_n.jpg"),
	//				Texture::textureManager.getPointer("snow_grass_s.jpg"),
	//				glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);
	//Material mirror(nullptr, Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);

	Material brick(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr,
				   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
	Material sky(Texture::textureManager.getPointer("cube_skybox"), nullptr, nullptr);

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* playerModel = new Entity();
	playerModel->addComponent(new RenderComponent(Mesh::meshManager.getPointer("monkey3.obj"), test));
	playerModel->getLocalTransform().setScale(glm::vec3(0.1, 0.1, 0.1));
	playerModel->getLocalTransform().translate(glm::vec3(0.0, 0.0, 0.1));
	playerModel->getLocalTransform().rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	camera->addChildEntity(playerModel);

	//Entity* plane = new Entity();
	//plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), test));
	//m_gameWorld.rootEntity.addChildEntity(plane);
	m_skybox.reset(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), sky));
	m_gameWorld.currentSkyBox = m_skybox.get();

	//Entity* object = new Entity();
	//object->getLocalTransform().translate(glm::vec3(0.0, 1.0, -3.0));
	//object->addComponent(new RenderComponent(Mesh::meshManager.getPointer("monkey3.obj"), brick));
	//m_gameWorld.rootEntity.addChildEntity(object);


	Entity* object = new Entity();
	object->getLocalTransform().translate(glm::vec3(0.0, 1.0, -3.0));
	object->addComponent(new MovableComponent());
	CubeCameraComponent* reflectCam = new CubeCameraComponent(90, 1.0);
	object->addComponent(reflectCam);
	m_gameWorld.m_renderTargets.emplace_back(512, 512, reflectCam, 1);
	object->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), mirror, m_gameWorld.m_renderTargets[0].getTextureData()));
	m_gameWorld.rootEntity.addChildEntity(object);

	Entity* object2 = new Entity();
	object2->getLocalTransform().translate(glm::vec3(0.0, 1.0, 3.0));
	CubeCameraComponent* reflectCam2 = new CubeCameraComponent(90, 1.0);
	object2->addComponent(reflectCam2);
	m_gameWorld.m_renderTargets.emplace_back(512, 512, reflectCam2, 1);
	//object2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), mirror, m_gameWorld.m_renderTargets[1].getTextureData()));
	object2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("sphere.obj"), mirror, m_gameWorld.m_renderTargets[1].getTextureData()));
	m_gameWorld.rootEntity.addChildEntity(object2);

	/*Entity* skyLight1 = new Entity();
	skyLight1->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight1->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight1->addComponent(new DirectionalLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.6f, false));
	m_gameWorld.rootEntity.addChildEntity(skyLight1);

	m_gameWorld.ambientLight = glm::vec3(0.2, 0.2, 0.2);*/
}
