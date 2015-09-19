#pragma once

#include "LightShader.hpp"
#include "../lighting/DirectionalLight.hpp"

class ForwardDirectionalLightShader : public LightShader {
public:
	ForwardDirectionalLightShader();

	void setDirectionalLight(const DirectionalLight& light);
};



