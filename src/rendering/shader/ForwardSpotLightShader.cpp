#include "ForwardSpotLightShader.hpp"

ForwardSpotLightShader::ForwardSpotLightShader() : LightShader("forward_spot_vert.glsl", "forward_spot_frag.glsl") {
	addUniform("spotLight.pointLight.base.colour");
	addUniform("spotLight.pointLight.base.luminosity");
	addUniform("spotLight.pointLight.position");
	addUniform("spotLight.pointLight.range");
	addUniform("spotLight.direction");
	addUniform("spotLight.cosineFov");
}

void ForwardSpotLightShader::setSpotLight(const SpotLightComponent& light) {
	setUniform("spotLight.pointLight.base.colour", light.getColour());
	setUniform("spotLight.pointLight.base.luminosity", light.getLuminosity());
	setUniform("spotLight.pointLight.position", light.getTransform().getTranslation());
	setUniform("spotLight.pointLight.range", light.getRange());
	setUniform("spotLight.direction", light.getTransform().getDirection());
	setUniform("spotLight.cosineFov", light.getCosineFov());
}
