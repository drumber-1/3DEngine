#include "DirectionalLightComponent.hpp"

#include "../../rendering/Renderer.hpp"
#include "../camera/OrthographicCameraComponent.hpp"

void DirectionalLightComponent::addToWorld(GameWorld* world) const {
	world->addDirectionalLight(this);
}

ShadowFramebuffer* DirectionalLightComponent::generateFrameBuffer() {
	return new ShadowFramebuffer(1024, 1024, 1.0f, false);
}

BaseCameraComponent* DirectionalLightComponent::generateCamera() {
	return new OrthographicCameraComponent(-5, 5, -5, 5);
}




