#include "PointLightComponent.hpp"

#include "../../rendering/Renderer.hpp"
#include "../camera/PerspectiveCameraComponent.hpp"

void PointLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addPointLight(this);
}

ShadowFramebuffer* PointLightComponent::generateFrameBuffer() {
	return new ShadowFramebuffer(1024, 1024, false);
}

BaseCameraComponent* PointLightComponent::generateCamera() {
	return new PerspectiveCameraComponent(170, 1.0f);
}
