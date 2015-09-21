#include "PointLightComponent.hpp"

#include "../rendering/Renderer.hpp"

void PointLightComponent::addToEngine(Engine* engine) const {
	engine->getRenderer()->addPointLight(this);
}
