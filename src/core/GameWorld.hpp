#pragma once

#include "../components/camera/BaseCameraComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "RootEntity.hpp"
#include "Entity.hpp"
#include "../components/lights/DirectionalLightComponent.hpp"
#include "../components/lights/PointLightComponent.hpp"
#include "../components/lights/SpotLightComponent.hpp"
#include "../rendering/RenderTarget.hpp"

class GameWorld {
public:
	GameWorld() : rootEntity(this),
				  currentCamera(nullptr),
				  currentSkyBox(nullptr),
				  ambientLight(glm::vec3(1.0, 1.0, 1.0)) { }

	RootEntity rootEntity;
	BaseCameraComponent* currentCamera;
	RenderComponent* currentSkyBox;
	glm::vec3 ambientLight;

	std::vector<const DirectionalLightComponent*> m_directionalLights;
	std::vector<const PointLightComponent*> m_pointLights;
	std::vector<const SpotLightComponent*> m_spotLights;

	std::vector<RenderTarget> m_renderTargets;

	inline void addDirectionalLight(const DirectionalLightComponent* light) { m_directionalLights.push_back(light); }
	inline void addPointLight(const PointLightComponent* light) { m_pointLights.push_back(light); }
	inline void addSpotLight(const SpotLightComponent* light) { m_spotLights.push_back(light); }
};
