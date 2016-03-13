#include "TestGame2.hpp"

#include "../components/RenderComponent.hpp"
#include "../components/FPCameraComponent.hpp"

#include <ctime>

std::vector<std::string> loadModels() {
	std::vector<std::string> models;

	Mesh::meshManager.emplace("cube.obj");
	models.push_back("cube.obj");

	Mesh::meshManager.emplace("monkey3.obj");
	models.push_back("monkey3.obj");

	Model modelPlane;
	modelPlane.makePlane(100, 100, 1);
	modelPlane.finalize();
	Mesh::meshManager.emplace("plane", modelPlane);
	models.push_back("plane");

	return models;
}

std::vector<Material> loadMaterials() {
	Texture::textureManager.emplace("test.png");
	Texture::textureManager.emplace("bricks.jpg");
	Texture::textureManager.emplace("bricks.jpg");

	std::vector<Material> materials;
	materials.emplace_back(Texture::textureManager.getPointer("test.png"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials.emplace_back(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

	return materials;
}

TestGame2::TestGame2(Engine* engine) : Game(engine) {

	std::vector<std::string> models = loadModels();
	std::vector<Material> materials = loadMaterials();


	Entity* camera = new Entity();
	CameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_rootEntity.addChildEntity(camera);
	m_currentCamera = cameraComponent;

	Entity* cameraLight = new Entity();
	cameraLight->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100));
	camera->addChildEntity(cameraLight);

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), materials[0]));
	m_rootEntity.addChildEntity(plane);

	Entity* skyLight = new Entity();
	skyLight->getLocalTransform().rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	skyLight->getLocalTransform().rotate(glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
	skyLight->addComponent(new DirectionalLightComponent(glm::vec3(0.2, 0.4, 0.6), 0.4f));
	m_rootEntity.addChildEntity(skyLight);

	std::srand((unsigned int)std::time(0));
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			float x = (i - 5) * 2.0f;
			float y = 1.0f;
			float z = (j - 5) * 2.0f;

			Entity* object = new Entity();
			object->getLocalTransform().translate(glm::vec3(x, y, z));
			std::string model = models[std::rand() % (models.size() - 1)];
			Material material = materials[std::rand() % materials.size()];
			object->addComponent(new RenderComponent(Mesh::meshManager.getPointer(model), material));
			m_rootEntity.addChildEntity(object);

		}
	}
}
