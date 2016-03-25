#pragma once

#include "BaseLightComponent.hpp"

#include "../../core/Engine.hpp"

class DirectionalLightComponent : public BaseLightComponent {
public:
	DirectionalLightComponent(const glm::vec3& colour,
							  float luminosity) : BaseLightComponent(colour, luminosity) {
	}

	virtual void addToEngine(Engine* engine) const;
};
