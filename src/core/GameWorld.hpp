#pragma once

#include "../components/CameraComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "RootEntity.hpp"

class GameWorld {
public:
	GameWorld(Engine* engine) : rootEntity(engine),
								currentCamera(nullptr),
								currentSkyBox(nullptr),
	                            ambientLight(glm::vec3(1.0, 1.0, 1.0)) {}
	RootEntity rootEntity;
	CameraComponent* currentCamera;
	RenderComponent* currentSkyBox;
	glm::vec3 ambientLight;
};
