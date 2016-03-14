#include "TextureTest.hpp"

#include "../../components/RenderComponent.hpp"
#include "../../components/FPCameraComponent.hpp"
#include "../../components/MovableComponent.hpp"

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
	Texture::textureManager.emplace("bricks_normal.jpg");
	Texture::textureManager.emplace("adesert_mntn4_d.jpg");
	Texture::textureManager.emplace("adesert_mntn4_n.jpg");
	Texture::textureManager.emplace("adesert_mntn4_s.jpg");
	Texture::textureManager.emplace("desert_cracks_d.jpg");
	Texture::textureManager.emplace("desert_cracks_n.jpg");
	Texture::textureManager.emplace("desert_cracks_s.jpg");
	Texture::textureManager.emplace("desert_sand_big_d.jpg");
	Texture::textureManager.emplace("desert_sand_big_n.jpg");
	Texture::textureManager.emplace("desert_sand_big_s.jpg");
	Texture::textureManager.emplace("desert_sand_d.jpg");
	Texture::textureManager.emplace("desert_sand_n.jpg");
	Texture::textureManager.emplace("desert_sand_s.jpg");
	Texture::textureManager.emplace("grass_autumn_d.jpg");
	Texture::textureManager.emplace("grass_autumn_n.jpg");
	Texture::textureManager.emplace("grass_autumn_s.jpg");
	Texture::textureManager.emplace("grass_rocky_d.jpg");
	Texture::textureManager.emplace("grass_rocky_n.jpg");
	Texture::textureManager.emplace("grass_rocky_s.jpg");
	Texture::textureManager.emplace("ground_cracked_d.jpg");
	Texture::textureManager.emplace("ground_cracked_n.jpg");
	Texture::textureManager.emplace("ground_cracked_s.jpg");
	Texture::textureManager.emplace("jungle_stone_d.jpg");
	Texture::textureManager.emplace("jungle_stone_n.jpg");
	Texture::textureManager.emplace("jungle_stone_s.jpg");
	Texture::textureManager.emplace("lava_d.jpg");
	Texture::textureManager.emplace("lava_n.jpg");
	Texture::textureManager.emplace("lava_s.jpg");
	Texture::textureManager.emplace("moss_plants_d.jpg");
	Texture::textureManager.emplace("moss_plants_n.jpg");
	Texture::textureManager.emplace("moss_plants_s.jpg");
	Texture::textureManager.emplace("snow_bumpy_d.jpg");
	Texture::textureManager.emplace("snow_bumpy_n.jpg");
	Texture::textureManager.emplace("snow_bumpy_s.jpg");
	Texture::textureManager.emplace("snow_d.jpg");
	Texture::textureManager.emplace("snow_n.jpg");
	Texture::textureManager.emplace("snow_s.jpg");
	Texture::textureManager.emplace("snow_grass_d.jpg");
	Texture::textureManager.emplace("snow_grass_n.jpg");
	Texture::textureManager.emplace("snow_grass_s.jpg");


	std::vector<Material> materials;
	materials.emplace_back(Texture::textureManager.getPointer("test.png"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials.emplace_back(Texture::textureManager.getPointer("bricks.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0, Texture::textureManager.getPointer("bricks_normal.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("adesert_mntn4_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("adesert_mntn4_n.jpg"), Texture::textureManager.getPointer("adesert_mntn4_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_cracks_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("desert_cracks_n.jpg"), Texture::textureManager.getPointer("desert_cracks_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_sand_big_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("desert_sand_big_n.jpg"), Texture::textureManager.getPointer("desert_sand_big_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_sand_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("desert_sand_n.jpg"), Texture::textureManager.getPointer("desert_sand_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("grass_autumn_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("grass_autumn_n.jpg"), Texture::textureManager.getPointer("grass_autumn_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("grass_rocky_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("grass_rocky_n.jpg"), Texture::textureManager.getPointer("grass_rocky_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("ground_cracked_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("ground_cracked_n.jpg"), Texture::textureManager.getPointer("ground_cracked_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("jungle_stone_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("jungle_stone_n.jpg"), Texture::textureManager.getPointer("jungle_stone_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("lava_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("lava_n.jpg"), Texture::textureManager.getPointer("lava_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("moss_plants_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("moss_plants_n.jpg"), Texture::textureManager.getPointer("moss_plants_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_bumpy_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("snow_bumpy_n.jpg"), Texture::textureManager.getPointer("snow_bumpy_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("snow_n.jpg"), Texture::textureManager.getPointer("snow_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_grass_d.jpg"), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 32, Texture::textureManager.getPointer("snow_grass_n.jpg"), Texture::textureManager.getPointer("snow_grass_s.jpg"));
	return materials;
}

TextureTest::TextureTest(Engine* engine) : Game(engine) {

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

	Entity* probe = new Entity();
	probe->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, -0.5f));
	probe->getLocalTransform().scale(glm::vec3(0.1f, 0.1f, 0.1f));
	probe->addComponent(new RenderComponent(Mesh::meshManager.getPointer(models[0]), materials[1]));
	probe->addComponent(new PointLightComponent(glm::vec3(1.0, 1.0, 1.0), 0.8f, 100));
	probe->addComponent(new MovableComponent());
	m_rootEntity.addChildEntity(probe);

	std::srand((unsigned int)std::time(0));
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			float x = (i - 5) * 2.0f;
			float y = 1.0f;
			float z = (j - 5) * 2.0f;

			Entity* object = new Entity();
			object->getLocalTransform().translate(glm::vec3(x, y, z));
			std::string model = models[(i + 11*j) % (models.size() - 1)];
			Material material = materials[(i + 11*j) % materials.size()];
			object->addComponent(new RenderComponent(Mesh::meshManager.getPointer(model), material));
			m_rootEntity.addChildEntity(object);

		}
	}
}
