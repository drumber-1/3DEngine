#include "ForwardSpotLightShader.hpp"

ForwardSpotLightShader::ForwardSpotLightShader() : LightShader("forward_spot_vert.glsl", "forward_spot_frag.glsl") {
	addUniform("spotLight.pointLight.base.colour");
	addUniform("spotLight.pointLight.base.luminosity");
	addUniform("spotLight.pointLight.base.xray");
	addUniform("spotLight.pointLight.position");
	addUniform("spotLight.pointLight.range");
	addUniform("spotLight.pointLight.attenuation.quadratic");
	addUniform("spotLight.pointLight.attenuation.linear");
	addUniform("spotLight.pointLight.attenuation.constant");
	addUniform("spotLight.direction");
	addUniform("spotLight.cosineFov");

	addUniform("lightSpaceMatrix");
	setTextureUnit("shadowMap");
}

void ForwardSpotLightShader::setSpotLight(const SpotLightComponent& light) {
	setUniform("spotLight.pointLight.base.colour", light.getColour());
	setUniform("spotLight.pointLight.base.luminosity", light.getLuminosity());
	setUniform("spotLight.pointLight.position", light.getPosition());
	setUniform("spotLight.pointLight.range", light.getRange());
	setUniform("spotLight.pointLight.attenuation.quadratic", light.getAttenuation().quadratic);
	setUniform("spotLight.pointLight.attenuation.linear", light.getAttenuation().linear);
	setUniform("spotLight.pointLight.attenuation.constant", light.getAttenuation().constant);
	setUniform("spotLight.direction", light.getDirection());
	setUniform("spotLight.cosineFov", light.getCosineFov());
	if (!light.isXray()) {
		setUniform("shadowMap", light.getShadowMapBuffer()->getShadowMap());
		setUniform("lightSpaceMatrix", light.getCamera()->getWorldToProjectionMatrix());
	}
}
