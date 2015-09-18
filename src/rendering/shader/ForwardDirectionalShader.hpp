#pragma once

#include "LightShader.hpp"
#include "../lighting/DirectionalLight.hpp"

class ForwardDirectionalShader : public LightShader {
public:
	ForwardDirectionalShader();

	void setDirectionalLight(const DirectionalLight& light);
};



