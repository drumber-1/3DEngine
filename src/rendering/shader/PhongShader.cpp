#include "PhongShader.hpp"
#include "../texture/Texture.hpp"

PhongShader::PhongShader(): Shader("phong_vert.glsl", "phong_frag.glsl") {
	addUniform("modelToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("modColour");
	addUniform("ambientLight");

	addUniform("directionalLight.base.colour");
	addUniform("directionalLight.base.luminosity");
	addUniform("directionalLight.direction");
}

void PhongShader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	material.getTexture()->bind();
}

void PhongShader::setDirectiobalLight(const DirectionalLight &directionalLight) {
	setUniform("directionalLight.base.colour", directionalLight.getColour());
	setUniform("directionalLight.base.luminosity", directionalLight.getLuminosity());
	setUniform("directionalLight.direction", directionalLight.getDirection());
}
