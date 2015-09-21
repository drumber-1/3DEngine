#pragma once

#include "PointLightComponent.hpp"

class SpotLightComponent : public PointLightComponent {
public:
	SpotLightComponent(const glm::vec3& colour,
					   float luminosity,
					   float range,
					   float cosineFov) : PointLightComponent(colour, luminosity, range),
										  m_cosineFov(cosineFov) { }

	inline float getCosineFov() const { return m_cosineFov; }
	inline void setCosineFov(float cosineFov) { m_cosineFov = cosineFov; }
private:
	float m_cosineFov;
};



