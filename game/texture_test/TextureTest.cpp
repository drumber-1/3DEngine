#include "TextureTest.hpp"

#include "../../src/components/camera/FPCameraComponent.hpp"

#include <ctime>

std::vector<std::string> loadModels() {
	std::vector<std::string> models;

	Mesh::meshManager.emplace("cube.obj");
	models.push_back("cube.obj");

	Mesh::meshManager.emplace("monkey3.obj");
	models.push_back("monkey3.obj");

	Model modelPlane;
	modelPlane.makePlane(25, 25, 1);
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
	materials.emplace_back(Texture::textureManager.getPointer("test.png"));
	materials.emplace_back(Texture::textureManager.getPointer("bricks.jpg"), Texture::textureManager.getPointer("bricks_normal.jpg"), nullptr,
						   glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
	materials.emplace_back(Texture::textureManager.getPointer("adesert_mntn4_d.jpg"),
						   Texture::textureManager.getPointer("adesert_mntn4_n.jpg"),
						   Texture::textureManager.getPointer("adesert_mntn4_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_cracks_d.jpg"),
						   Texture::textureManager.getPointer("desert_cracks_n.jpg"),
						   Texture::textureManager.getPointer("desert_cracks_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_sand_big_d.jpg"),
						   Texture::textureManager.getPointer("desert_sand_big_n.jpg"),
						   Texture::textureManager.getPointer("desert_sand_big_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("desert_sand_d.jpg"),
						   Texture::textureManager.getPointer("desert_sand_n.jpg"),
						   Texture::textureManager.getPointer("desert_sand_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("grass_autumn_d.jpg"),
						   Texture::textureManager.getPointer("grass_autumn_n.jpg"),
						   Texture::textureManager.getPointer("grass_autumn_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("grass_rocky_d.jpg"),
						   Texture::textureManager.getPointer("grass_rocky_n.jpg"),
						   Texture::textureManager.getPointer("grass_rocky_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("ground_cracked_d.jpg"),
						   Texture::textureManager.getPointer("ground_cracked_n.jpg"),
						   Texture::textureManager.getPointer("ground_cracked_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("jungle_stone_d.jpg"),
						   Texture::textureManager.getPointer("jungle_stone_n.jpg"),
						   Texture::textureManager.getPointer("jungle_stone_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("lava_d.jpg"),
						   Texture::textureManager.getPointer("lava_n.jpg"),
						   Texture::textureManager.getPointer("lava_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("moss_plants_d.jpg"),
						   Texture::textureManager.getPointer("moss_plants_n.jpg"),
						   Texture::textureManager.getPointer("moss_plants_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_bumpy_d.jpg"),
						   Texture::textureManager.getPointer("snow_bumpy_n.jpg"),
						   Texture::textureManager.getPointer("snow_bumpy_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_d.jpg"),
						   Texture::textureManager.getPointer("snow_n.jpg"),
						   Texture::textureManager.getPointer("snow_s.jpg"));
	materials.emplace_back(Texture::textureManager.getPointer("snow_grass_d.jpg"),
						   Texture::textureManager.getPointer("snow_grass_n.jpg"),
						   Texture::textureManager.getPointer("snow_grass_s.jpg"));
	return materials;
}

TextureTest::TextureTest() {

	std::vector<std::string> models = loadModels();
	std::vector<Material> materials = loadMaterials();

	Texture::textureManager.emplace("cube_skybox");
	Material sky(Texture::textureManager.getPointer("cube_skybox"));
	m_skybox.reset(new RenderComponent(Mesh::meshManager.getPointer("cube.obj"), sky));
	m_gameWorld.currentSkyBox = m_skybox.get();

	Entity* camera = new Entity();
	BaseCameraComponent* cameraComponent = new FPCameraComponent(70, 1.0);
	camera->addComponent(cameraComponent);
	camera->getLocalTransform().translate(glm::vec3(0.0f, 1.0f, 0.0f));
	m_gameWorld.rootEntity.addChildEntity(camera);
	m_gameWorld.currentCamera = cameraComponent;

	Entity* plane = new Entity();
	plane->addComponent(new RenderComponent(Mesh::meshManager.getPointer("plane"), materials[0]));
	m_gameWorld.rootEntity.addChildEntity(plane);

	std::srand((unsigned int) std::time(0));
	for (int i = 0; i <= 10; i++) {
		for (int j = 0; j <= 10; j++) {
			float x = (i - 5) * 2.0f;
			float y = 1.0f;
			float z = (j - 5) * 2.0f;

			Entity* object = new Entity();
			object->getLocalTransform().translate(glm::vec3(x, y, z));
			std::string model = models[(i + 11 * j) % (models.size() - 1)];
			Material material = materials[(i + 11 * j) % materials.size()];
			object->addComponent(new RenderComponent(Mesh::meshManager.getPointer(model), material));
			m_gameWorld.rootEntity.addChildEntity(object);
		}
	}

	m_gameWorld.ambientLight = glm::vec3(0.5, 0.5, 0.5);
}
