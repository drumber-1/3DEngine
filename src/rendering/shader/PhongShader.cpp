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

void PhongShader::setModelToProjectionMatrix(glm::mat4 matrix) {
	setUniform("modelToProjectionMatrix", matrix);
}

void PhongShader::setModelToWorldMatrix(glm::mat4 matrix) {
	setUniform("modelToWorldMatrix", matrix);
}

void PhongShader::setModColour(glm::vec4 colour) {
	setUniform("modColour", colour);
}

void PhongShader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	material.getTexture()->bind();
}

void PhongShader::setAmbientLight(glm::vec3 ambientLight) {
	setUniform("ambientLight", ambientLight);
}

void PhongShader::setDirectiobalLight(const DirectionalLight &directionalLight) {
	setUniform("directionalLight.base.colour", directionalLight.getColour());
	setUniform("directionalLight.base.luminosity", directionalLight.getLuminosity());
	setUniform("directionalLight.direction", directionalLight.getDirection());
}
