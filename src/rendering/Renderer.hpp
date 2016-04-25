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
#include "shader/ShadowDepthCubeShader.hpp"
#include "shader/ReflectionShader.hpp"
#include "framebuffer/FrameBuffer.hpp"

class DirectionalLightComponent;

class PointLightComponent;

class SpotLightComponent;

class Renderer {
public:
	Renderer(Window* window);

	virtual ~Renderer() { }

	void render(GameWorld& gameWorld);

private:
	const Window* m_window;

	ForwardAmbientLightShader m_ambientLightShader;
	ForwardDirectionalLightShader m_directionalLightShader;
	ForwardPointLightShader m_pointLightShader;
	ForwardSpotLightShader m_spotLightShader;

	SkyboxShader m_skyboxShader;
	ReflectionShader m_reflectionShader;
	ShadowDepthShader m_shadowShader;
	ShadowDepthCubeShader m_shadowCubeShader;

	std::vector<const FrameBuffer*> m_renderTargets;

	void renderScene(const GameWorld& gameWorld, const BaseCameraComponent* cameraComponent);

	void renderShadows(const GameWorld& gameWorld, const BaseLightComponent* light, Shader& shader);

	void enableBlending();

	void disableBlending();
};
