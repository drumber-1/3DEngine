#include "ForwardAmbientLightShader.hpp"

ForwardAmbientLightShader::ForwardAmbientLightShader() : Shader("forward_ambient_vert.glsl",
																"forward_ambient_frag.glsl") {
	addUniform("ambientLight");
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("modColour");

	setTextureUnit("theTexture");
}

void ForwardAmbientLightShader::setAmbientLight(const glm::vec3& ambientLight) {
	setUniform("ambientLight", ambientLight);
}

void ForwardAmbientLightShader::setCamera(const BaseCameraComponent& camera) {
	setUniform("worldToProjectionMatrix", camera.getWorldToProjectionMatrix());
}

void ForwardAmbientLightShader::setMaterial(const Material& material) {
	setUniform("modColour", material.getModColour());
	setUniform("theTexture", material.getTexture());
}

void ForwardAmbientLightShader::draw(const RenderComponent& renderComponent) {
	if (!renderComponent.material.hasDiffuse()) {
		return;
	}
	setMaterial(renderComponent.material);
	setUniform("modelToWorldMatrix", renderComponent.getTransformationMatrix());
	renderComponent.mesh->draw();
}