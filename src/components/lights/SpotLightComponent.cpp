#include "SpotLightComponent.hpp"

#include "../../rendering/Renderer.hpp"
#include "../camera/PerspectiveCameraComponent.hpp"

void SpotLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addSpotLight(this);
}

ShadowFramebuffer* SpotLightComponent::generateFrameBuffer() {
	return new ShadowFramebuffer(1024, 1024, 1.0f, false);
}

BaseCameraComponent* SpotLightComponent::generateCamera() {
	return new PerspectiveCameraComponent(std::cos(m_cosineFov), 1.0f);
}




