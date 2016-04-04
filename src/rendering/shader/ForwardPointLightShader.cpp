#include "ForwardPointLightShader.hpp"

ForwardPointLightShader::ForwardPointLightShader() : LightShader("forward_point_vert.glsl", "forward_point_frag.glsl") {
	addUniform("pointLight.base.colour");
	addUniform("pointLight.base.luminosity");
	addUniform("pointLight.base.xray");
	addUniform("pointLight.position");
	addUniform("pointLight.range");

	addUniform("lightSpaceMatrix");
	setTextureUnit("shadowMap");
}

void ForwardPointLightShader::setPointLight(const PointLightComponent& light) {
	setUniform("pointLight.base.colour", light.getColour());
	setUniform("pointLight.base.luminosity", light.getLuminosity());
	setUniform("pointLight.position", light.getPosition());
	setUniform("pointLight.range", light.getRange());
	if (!light.isXray()) {
		setUniform("shadowMap", light.getShadowMapBuffer()->getShadowMap());
		setUniform("lightSpaceMatrix", light.getCamera()->getWorldToProjectionMatrix());
	}
}
