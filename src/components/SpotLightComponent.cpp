#include "SpotLightComponent.hpp"

#include "../rendering/Renderer.hpp"

void SpotLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addSpotLight(this);
}
