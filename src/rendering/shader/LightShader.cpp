#include "LightShader.hpp"

LightShader::LightShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader,
																									  fragmentShader) {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("modColour");

	addUniform("eyePositionWorld");
	addUniform("reflectivity");
	addUniform("specularIndex");

	setTextureUnit("theTexture");
	setTextureUnit("theNormal");
	setTextureUnit("theSpec");
}

void LightShader::setCamera(const BaseCameraComponent& camera) {
	setUniform("worldToProjectionMatrix", camera.getWorldToProjectionMatrix());
	setUniform("eyePositionWorld", camera.getPosition());
}

void LightShader::setMaterial(const Material& material) {
	setUniform("modColour", material.getModColour());
	setUniform("theTexture", material.getTexture());
	setUniform("theNormal", material.getNormal());
	setUniform("theSpec", material.getSpec());
	setUniform("reflectivity", material.getReflectivity());
	setUniform("specularIndex", material.getSpecularIndex());
}

void LightShader::draw(const RenderComponent& renderComponent) {
	if (!renderComponent.material.hasDiffuse()) {
		return''
	}
	setMaterial(renderComponent.material);
	setUniform("modelToWorldMatrix", renderComponent.getTransformationMatrix());
	renderComponent.mesh->draw();
}
