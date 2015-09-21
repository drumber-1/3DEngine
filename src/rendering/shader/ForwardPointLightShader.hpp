#pragma once

#include "LightShader.hpp"
#include "../../components/PointLightComponent.hpp"

class ForwardPointLightShader : public LightShader {
public:
	ForwardPointLightShader();

	void setPointLight(const PointLightComponent& light);
};



