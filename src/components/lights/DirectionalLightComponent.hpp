#pragma once

#include "BaseLightComponent.hpp"

#include "../../core/Engine.hpp"
#include "../camera/BaseCameraComponent.hpp"

class DirectionalLightComponent : public BaseLightComponent {
public:
	DirectionalLightComponent(const glm::vec3& colour,
							  float luminosity,
							  bool xray = false) : BaseLightComponent(colour, luminosity, xray) {}

	virtual void addToEngine(Engine* engine) const;
protected:
	virtual ShadowFramebuffer* generateFrameBuffer() override;
	virtual BaseCameraComponent* generateCamera() override;
};
