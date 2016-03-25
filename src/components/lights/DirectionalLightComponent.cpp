#include "DirectionalLightComponent.hpp"

#include "../../rendering/Renderer.hpp"

void DirectionalLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addDirectionalLight(this);
}
