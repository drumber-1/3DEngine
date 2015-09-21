#pragma once

#include "LightShader.hpp"
#include "../../components/DirectionalLightComponent.hpp"

class ForwardDirectionalLightShader : public LightShader {
public:
	ForwardDirectionalLightShader();

	void setDirectionalLight(const DirectionalLightComponent& light);
};



