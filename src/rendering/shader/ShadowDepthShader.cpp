#include "ShadowDepthShader.hpp"

ShadowDepthShader::ShadowDepthShader() : Shader("shadow_depth_vert.glsl", "shadow_depth_frag.glsl") {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
}

void ShadowDepthShader::setCamera(const BaseCameraComponent &camera) {
	setUniform("worldToProjectionMatrix", camera.getWorldToProjectionMatrix());
}

void ShadowDepthShader::draw(const RenderComponent &renderComponent) {
	setUniform("modelToWorldMatrix", renderComponent.getTransformationMatrix());
	renderComponent.mesh->draw();
}