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
	}
}

void PhongShader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	setReflectivity(material.getReflectivity());
	setSpecularIndex(material.getSpecularIndex());
	material.getTexture()->bind();
}

void PhongShader::setDirectionalLight(const DirectionalLight &directionalLight, int id) {
	setUniform("directionalLights[" + std::to_string(id) + "].base.colour", directionalLight.getColour());
	setUniform("directionalLights[" + std::to_string(id) + "].base.luminosity", directionalLight.getLuminosity());
	setUniform("directionalLights[" + std::to_string(id) + "].direction", directionalLight.getDirection());
}

void PhongShader::setPointLight(const PointLight &pointLight, int id) {
	setUniform("pointLights[" + std::to_string(id) + "].base.colour", pointLight.getColour());
	setUniform("pointLights[" + std::to_string(id) + "].base.luminosity", pointLight.getLuminosity());
	setUniform("pointLights[" + std::to_string(id) + "].position", pointLight.getPosition());
}
