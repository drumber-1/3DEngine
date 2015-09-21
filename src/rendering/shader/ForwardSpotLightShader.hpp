#pragma once

#include "LightShader.hpp"
#include "../../components/SpotLightComponent.hpp"

class ForwardSpotLightShader : public LightShader {
public:
	ForwardSpotLightShader();

	void setSpotLight(const SpotLightComponent& light);
};



