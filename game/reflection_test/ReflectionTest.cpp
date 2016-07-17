#include "ReflectionTest.hpp"

#include "../../src/components/camera/FPCameraComponent.hpp"
#include "../../src/components/MovableComponent.hpp"

ReflectionTest::ReflectionTest() {

	Mesh::meshManager.emplace("cube.obj");
	Mesh::meshManager.emplace("sphere.obj");
	Texture::textureManager.emplace("cube_skybox");

	Material mirror(nullptr, nullptr, nullptr, glm::vec4(1.0, 1.0, 1.0, 1.0), 1.0f, 32.0f, true);

	Material sky(Texture::textureManager.getPointer("cube_skybox"), nullptr, nullptr);

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	m_skybox.reset(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), sky));
	m_gameWorld.currentSkyBox = m_skybox.get();

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
	object2->addComponent(new RenderComponent(Mesh::meshManager.getPointer("sphere.obj"), mirror, m_gameWorld.m_renderTargets[1].getTextureData()));
	m_gameWorld.rootEntity.addChildEntity(object2);

}
