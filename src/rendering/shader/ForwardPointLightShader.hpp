#pragma once

#include "LightShader.hpp"
#include "../../components/lights/PointLightComponent.hpp"

class ForwardPointLightShader : public LightShader {
public:
	ForwardPointLightShader();

	virtual void setCamera(const BaseCameraComponent& camera) override;

	void setPointLight(const PointLightComponent& light);
};



