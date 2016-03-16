//
// Created by jake on 16/03/16.
//

#include "SkyboxShader.hpp"

SkyboxShader::SkyboxShader() : BaseShader("skybox_vert.glsl", "skybox_frag.glsl") {
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

void SkyboxShader::setModColour(const glm::vec4& colour) {
	setUniform("modColour", colour);
}

void SkyboxShader::setAmbientLight(const glm::vec3& ambientLight) {
	setUniform("ambientLight", ambientLight);
}
