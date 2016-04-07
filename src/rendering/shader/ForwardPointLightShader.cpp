#include "ForwardPointLightShader.hpp"

ForwardPointLightShader::ForwardPointLightShader() : LightShader("forward_point_vert.glsl", "forward_point_frag.glsl") {
	addUniform("pointLight.base.colour");
	addUniform("pointLight.base.luminosity");
	addUniform("pointLight.base.xray");
	addUniform("pointLight.position");
	addUniform("pointLight.range");
	addUniform("pointLight.attenuation.quadratic");
	addUniform("pointLight.attenuation.linear");
	addUniform("pointLight.attenuation.constant");
	addUniform("farPlane");

	setTextureUnit("shadowMap");
}

void ForwardPointLightShader::setPointLight(const PointLightComponent& light) {
	setUniform("pointLight.base.colour", light.getColour());
	setUniform("pointLight.base.luminosity", light.getLuminosity());
	setUniform("pointLight.base.xray", light.isXray());
	setUniform("pointLight.position", light.getPosition());
	setUniform("pointLight.range", light.getRange());
	setUniform("pointLight.attenuation.quadratic", light.getAttenuation().quadratic);
	setUniform("pointLight.attenuation.linear", light.getAttenuation().linear);
	setUniform("pointLight.attenuation.constant", light.getAttenuation().constant);
	if (!light.isXray()) {
		setUniform("shadowMap", light.getShadowMapBuffer()->getShadowMap());
	}
}

void ForwardPointLightShader::setCamera(const BaseCameraComponent& camera) {
	LightShader::setCamera(camera);
	setUniform("farPlane", camera.getFarPlane());
}
