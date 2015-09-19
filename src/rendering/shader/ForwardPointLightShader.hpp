#pragma once

#include "LightShader.hpp"
#include "../lighting/PointLight.hpp"

class ForwardPointLightShader : public LightShader {
public:
	ForwardPointLightShader();

	void setPointLight(const PointLight& light);
};



