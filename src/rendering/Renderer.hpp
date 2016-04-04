#pragma once

#include "Window.hpp"

#include "model/Mesh.hpp"

#include "shader/ForwardAmbientLightShader.hpp"
#include "shader/ForwardDirectionalLightShader.hpp"
#include "shader/ForwardPointLightShader.hpp"
#include "shader/ForwardSpotLightShader.hpp"
#include "shader/SkyboxShader.hpp"
#include "shader/ShadowDepthShader.hpp"

#include "../core/ModelToWorldTransform.hpp"
#include "../core/ResourceManager.hpp"
#include "../core/Entity.hpp"

#include "../components/camera/BaseCameraComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../core/GameWorld.hpp"
#include "framebuffer/ShadowFramebuffer.hpp"

class DirectionalLightComponent;
class PointLightComponent;
class SpotLightComponent;

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(GameWorld& gameWorld);

	inline void addDirectionalLight(const DirectionalLightComponent* light) { m_directionalLights.push_back(light); }
	inline void addPointLight(const PointLightComponent* light) { m_pointLights.push_back(light); }
	inline void addSpotLight(const SpotLightComponent* light) { m_spotLights.push_back(light); }

private:
	const Window* m_window;

	ForwardAmbientLightShader m_ambientLightShader;
	ForwardDirectionalLightShader m_directionalLightShader;
	ForwardPointLightShader m_pointLightShader;
	ForwardSpotLightShader m_spotLightShader;

	SkyboxShader m_skyboxShader;
	ShadowDepthShader m_shadowShader;

	std::vector<const DirectionalLightComponent*> m_directionalLights;
	std::vector<const PointLightComponent*> m_pointLights;
	std::vector<const SpotLightComponent*> m_spotLights;

	void renderScene(const GameWorld& gameWorld);
	void renderShadows(const GameWorld& gameWorld, const BaseCameraComponent& lightCamera);
	void renderSkybox(const GameWorld& gameWorld);
	void enableBlending();
	void disableBlending();
};
