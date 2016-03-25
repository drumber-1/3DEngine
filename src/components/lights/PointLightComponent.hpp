#pragma once

#include "BaseLightComponent.hpp"

class PointLightComponent : public BaseLightComponent {
public:
	PointLightComponent(const glm::vec3& colour, float luminosity, float range) : BaseLightComponent(colour, luminosity),
																				  m_range(range) {}
	inline float getRange() const { return m_range; }
	inline void setRange(float range) { m_range = range; }

	virtual void addToEngine(Engine* engine) const;
private:
	float m_range;
};



