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

class Renderer {
public:
	Renderer(Window* window);
	virtual ~Renderer() {}

	void render(const Camera& camera, const Entity& root);
	static ResourceManager<Mesh> meshManager;
	static ResourceManager<Texture> textureManager;
private:
	const Window* m_window;

	glm::vec3 m_ambientLight;

	ForwardAmbientLightShader m_ambientLightShader;
	ForwardDirectionalLightShader m_directionalLightShader;
	ForwardPointLightShader m_pointLightShader;
	ForwardSpotLightShader m_spotLightShader;

	DirectionalLight m_testDLight;
	PointLight m_testPLight;
	SpotLight m_testSLight;
};
