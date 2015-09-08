#include "PhongShader.hpp"
#include "../texture/Texture.hpp"

PhongShader::PhongShader(): Shader("phong_vert.glsl", "phong_frag.glsl") {
	addUniform("modelToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("eyePositionWorld");

	addUniform("modColour");
	addUniform("reflectivity");
	addUniform("specularIndex");

	addUniform("ambientLight");

	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; ++i) {
		addUniform("directionalLights[" + std::to_string(i) + "].base.colour");
		addUniform("directionalLights[" + std::to_string(i) + "].base.luminosity");
		addUniform("directionalLights[" + std::to_string(i) + "].direction");
	}

	for (int i = 0; i < MAX_POINT_LIGHTS; ++i) {
		addUniform("pointLights[" + std::to_string(i) + "].base.colour");
		addUniform("pointLights[" + std::to_string(i) + "].base.luminosity");
		addUniform("pointLights[" + std::to_string(i) + "].position");
		addUniform("pointLights[" + std::to_string(i) + "].range");
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; ++i) {
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.colour");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.base.luminosity");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.position");
		addUniform("spotLights[" + std::to_string(i) + "].pointLight.range");
		addUniform("spotLights[" + std::to_string(i) + "].direction");
		addUniform("spotLights[" + std::to_string(i) + "].cosineFov");
	}
}

void PhongShader::setMaterial(const Material& material) {
	setModColour(material.getModColour());
	setReflectivity(material.getReflectivity());
	setSpecularIndex(material.getSpecularIndex());
	material.getTexture()->bind();
}

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight, int id) {
	setUniform("directionalLights[" + std::to_string(id) + "].base.colour", directionalLight.getColour());
	setUniform("directionalLights[" + std::to_string(id) + "].base.luminosity", directionalLight.getLuminosity());
	setUniform("directionalLights[" + std::to_string(id) + "].direction", directionalLight.getDirection());
}

void PhongShader::setPointLight(const PointLight& pointLight, int id) {
	setUniform("pointLights[" + std::to_string(id) + "].base.colour", pointLight.getColour());
	setUniform("pointLights[" + std::to_string(id) + "].base.luminosity", pointLight.getLuminosity());
	setUniform("pointLights[" + std::to_string(id) + "].position", pointLight.getPosition());
	setUniform("pointLights[" + std::to_string(id) + "].range", pointLight.getRange());
}


void PhongShader::setSpotLight(const SpotLight& spotLight, int id) {
	setUniform("spotLights[" + std::to_string(id) + "].pointLight.base.colour", spotLight.getColour());
	setUniform("spotLights[" + std::to_string(id) + "].pointLight.base.luminosity", spotLight.getLuminosity());
	setUniform("spotLights[" + std::to_string(id) + "].pointLight.position", spotLight.getPosition());
	setUniform("spotLights[" + std::to_string(id) + "].pointLight.range", spotLight.getRange());
	setUniform("spotLights[" + std::to_string(id) + "].direction", spotLight.getDirection());
	setUniform("spotLights[" + std::to_string(id) + "].cosineFov", spotLight.getCosineFov());
}
