#pragma once

#include "LightShader.hpp"
#include "../../components/lights/DirectionalLightComponent.hpp"

class ForwardDirectionalLightShader : public LightShader {
public:
	ForwardDirectionalLightShader();

	void setDirectionalLight(const DirectionalLightComponent& light);
};



