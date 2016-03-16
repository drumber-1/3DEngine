#include "SkyboxShader.hpp"

SkyboxShader::SkyboxShader() : Shader("skybox_vert.glsl", "skybox_frag.glsl") {
	addUniform("worldToViewMatrix");
	addUniform("viewToProjectionMatrix");
	addUniform("modColour");
	addUniform("ambientLight");
	setTextureUnit("theTexture");
}

void SkyboxShader::setCamera(const CameraComponent& camera) {
	setUniform("worldToViewMatrix", camera.getWorldToViewMatrix());
	setUniform("viewToProjectionMatrix", camera.getViewToProjection());
}

void SkyboxShader::setAmbientLight(const glm::vec3& ambientLight) {
	setUniform("ambientLight", ambientLight);
}

void SkyboxShader::setMaterial(const Material &material) {
	setUniform("modColour", material.getModColour());
	setUniform("theTexture", material.getTexture());
}

void SkyboxShader::draw(const RenderComponent &renderComponent) {
	setMaterial(renderComponent.material);
	renderComponent.mesh->draw();
}
