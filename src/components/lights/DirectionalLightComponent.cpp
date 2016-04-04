#include "DirectionalLightComponent.hpp"

#include "../../rendering/Renderer.hpp"
#include "../camera/OrthographicCameraComponent.hpp"

void DirectionalLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addDirectionalLight(this);
}

ShadowFramebuffer* DirectionalLightComponent::generateFrameBuffer() {
	return new ShadowFramebuffer(1024, 1024, 1.0f);
}

BaseCameraComponent* DirectionalLightComponent::generateCamera() {
	return new OrthographicCameraComponent(-5, 5, -5, 5);
}




