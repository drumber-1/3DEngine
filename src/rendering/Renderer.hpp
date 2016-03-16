#pragma once

#include "Window.hpp"

#include "model/Mesh.hpp"

#include "shader/ForwardAmbientLightShader.hpp"
#include "shader/ForwardDirectionalLightShader.hpp"
#include "shader/ForwardPointLightShader.hpp"
#include "shader/ForwardSpotLightShader.hpp"

#include "../core/ModelToWorldTransform.hpp"
#include "../core/ResourceManager.hpp"
#include "../core/Entity.hpp"

#include "../components/CameraComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "shader/SkyboxShader.hpp"

class DirectionalLightComponent;
class PointLightComponent;
class SpotLightComponent;

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(const CameraComponent& camera, const Entity& root);

	inline void addDirectionalLight(const DirectionalLightComponent* light) { m_directionalLights.push_back(light); }
	inline void addPointLight(const PointLightComponent* light) { m_pointLights.push_back(light); }
	inline void addSpotLight(const SpotLightComponent* light) { m_spotLights.push_back(light); }

private:
	const Window* m_window;

	glm::vec3 m_ambientLight;

	ForwardAmbientLightShader m_ambientLightShader;
	ForwardDirectionalLightShader m_directionalLightShader;
	ForwardPointLightShader m_pointLightShader;
	ForwardSpotLightShader m_spotLightShader;

	SkyboxShader m_skyboxShader;

	std::vector<const DirectionalLightComponent*> m_directionalLights;
	std::vector<const PointLightComponent*> m_pointLights;
	std::vector<const SpotLightComponent*> m_spotLights;
};
