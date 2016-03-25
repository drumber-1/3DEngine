#pragma once

#include "LightShader.hpp"
#include "../../components/lights/SpotLightComponent.hpp"

class ForwardSpotLightShader : public LightShader {
public:
	ForwardSpotLightShader();

	void setSpotLight(const SpotLightComponent& light);
};



