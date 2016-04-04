#include "ForwardDirectionalLightShader.hpp"

ForwardDirectionalLightShader::ForwardDirectionalLightShader() : LightShader("forward_directional_vert.glsl", "forward_directional_frag.glsl") {
	addUniform("directionalLight.base.colour");
	addUniform("directionalLight.base.luminosity");
	addUniform("directionalLight.base.xray");
	addUniform("directionalLight.direction");

	addUniform("lightSpaceMatrix");
	setTextureUnit("shadowMap");
}

void ForwardDirectionalLightShader::setDirectionalLight(const DirectionalLightComponent& light) {
	setUniform("directionalLight.base.colour", light.getColour());
	setUniform("directionalLight.base.luminosity", light.getLuminosity());
	setUniform("directionalLight.base.xray", light.isXray());
	setUniform("directionalLight.direction", light.getDirection());
	if (!light.isXray()) {
		setUniform("shadowMap", light.getShadowMapBuffer()->getShadowMap());
		setUniform("lightSpaceMatrix", light.getCamera()->getWorldToProjectionMatrix());
	}
}
