#pragma once

#include "Window.hpp"
#include "Material.hpp"
#include "Camera.hpp"

#include "model/Mesh.hpp"

#include "shader/ForwardAmbientLightShader.hpp"
#include "shader/ForwardDirectionalLightShader.hpp"
#include "shader/ForwardPointLightShader.hpp"
#include "shader/ForwardSpotLightShader.hpp"

#include "../core/ModelToWorldTransform.hpp"
#include "../core/ResourceManager.hpp"
#include "../core/Entity.hpp"

class DirectionalLightComponent;
class PointLightComponent;
class SpotLightComponent;

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(const Camera& camera, const Entity& root);

	inline void addDirectionalLight(const DirectionalLightComponent* light) { m_directionalLights.push_back(light); }
	inline void addPointLight(const PointLightComponent* light) { m_pointLights.push_back(light); }
	inline void addSpotLight(const SpotLightComponent* light) { m_spotLights.push_back(light); }

	static ResourceManager<Mesh> meshManager;
	static ResourceManager<Texture> textureManager;
private:
	const Window* m_window;

	glm::vec3 m_ambientLight;

	ForwardAmbientLightShader m_ambientLightShader;
	ForwardDirectionalLightShader m_directionalLightShader;
	ForwardPointLightShader m_pointLightShader;
	ForwardSpotLightShader m_spotLightShader;

	std::vector<const DirectionalLightComponent*> m_directionalLights;
	std::vector<const PointLightComponent*> m_pointLights;
	std::vector<const SpotLightComponent*> m_spotLights;

//	DirectionalLight m_testDLight;
//	PointLight m_testPLight;
//	SpotLight m_testSLight;
};
