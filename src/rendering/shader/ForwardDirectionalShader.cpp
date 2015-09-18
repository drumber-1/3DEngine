#include "ForwardDirectionalShader.hpp"

ForwardDirectionalShader::ForwardDirectionalShader() : LightShader("forward_directional_vert.glsl", "forward_directional_frag.glsl") {
	addUniform("directionalLight.base.colour");
	addUniform("directionalLight.base.luminosity");
	addUniform("directionalLight.direction");
}

void ForwardDirectionalShader::setDirectionalLight(const DirectionalLight& light) {
	setUniform("directionalLight.base.colour", light.getColour());
	setUniform("directionalLight.base.luminosity", light.getLuminosity());
	setUniform("directionalLight.direction", light.getDirection());
}