#include "SpotLightComponent.hpp"

#include "../../rendering/Renderer.hpp"
#include "../camera/PerspectiveCameraComponent.hpp"

void SpotLightComponent::addToWorld(GameWorld* world) const {
	world->addSpotLight(this);
}

ShadowFramebuffer* SpotLightComponent::generateFrameBuffer() {
	return new ShadowFramebuffer(1024, 1024, 1.0f, false);
}

BaseCameraComponent* SpotLightComponent::generateCamera() {
	return new PerspectiveCameraComponent(360.0f * std::acos(m_cosineFov) / (float)M_PI, 1.0f);
}




