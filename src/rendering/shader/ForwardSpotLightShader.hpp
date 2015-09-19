#pragma once

#include "LightShader.hpp"
#include "../lighting/SpotLight.hpp"

class ForwardSpotLightShader : public LightShader {
public:
	ForwardSpotLightShader();

	void setPointLight(const SpotLight& light);
};



