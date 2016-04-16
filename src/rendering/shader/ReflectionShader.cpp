#include "ReflectionShader.hpp"

ReflectionShader::ReflectionShader() : Shader("forward_reflection_vert.glsl",
											  "forward_reflection_frag.glsl") {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	//addUniform("modColour");

	addUniform("eyePositionWorld");
	addUniform("reflectivity");
	//addUniform("specularIndex");

	setTextureUnit("reflectionMap");
	//setTextureUnit("theTexture");
	setTextureUnit("theNormal");
	setTextureUnit("theSpec");
}

void ReflectionShader::setCamera(const BaseCameraComponent& camera) {
	setUniform("worldToProjectionMatrix", camera.getWorldToProjectionMatrix());
	setUniform("eyePositionWorld", camera.getPosition());
}

void ReflectionShader::setMaterial(const Material& material) {
	//setUniform("modColour", material.getModColour());
	//setUniform("theTexture", material.getTexture());
	setUniform("theNormal", material.getNormal());
	setUniform("theSpec", material.getSpec());
	setUniform("reflectivity", material.getReflectivity());
	//setUniform("specularIndex", material.getSpecularIndex());
}

void ReflectionShader::draw(const RenderComponent& renderComponent) {
	if (!renderComponent.material.hasReflections()) {
		return;
	}
	setMaterial(renderComponent.material);
	setUniform("modelToWorldMatrix", renderComponent.getTransformationMatrix());
	setUniform("reflectionMap", renderComponent.reflectionMap);
	renderComponent.mesh->draw();
}