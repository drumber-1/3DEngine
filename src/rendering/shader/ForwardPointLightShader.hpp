#pragma once

#include "LightShader.hpp"
#include "../../components/lights/PointLightComponent.hpp"

class ForwardPointLightShader : public LightShader {
public:
	ForwardPointLightShader();

	void setPointLight(const PointLightComponent& light);
};



