#pragma once

#include "BaseLightComponent.hpp"

class DirectionalLightComponent : public BaseLightComponent {
public:
	DirectionalLightComponent(const glm::vec3& colour,
							  float luminosity) : BaseLightComponent(colour, luminosity) {
	}
};
