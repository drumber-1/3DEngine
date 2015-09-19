#include "ForwardPointLightShader.hpp"

ForwardPointLightShader::ForwardPointLightShader() : LightShader("forward_point_vert.glsl", "forward_point_frag.glsl") {
	addUniform("pointLight.base.colour");
	addUniform("pointLight.base.luminosity");
	addUniform("pointLight.position");
	addUniform("pointLight.range");
}

void ForwardPointLightShader::setPointLight(const PointLight& light) {
	setUniform("pointLight.base.colour", light.getColour());
	setUniform("pointLight.base.luminosity", light.getLuminosity());
	setUniform("pointLight.position", light.getPosition());
	setUniform("pointLight.range", light.getRange());
}
