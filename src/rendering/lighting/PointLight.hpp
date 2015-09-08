#pragma once

#include "BaseLight.hpp"

class PointLight : public BaseLight {
public:
	PointLight(const glm::vec3& colour, float luminosity, const glm::vec3& position, float range) : BaseLight(colour, luminosity),
																					                m_position(position),
																									m_range(range) {}

	inline const glm::vec3& getPosition() const { return m_position; }
	inline float getRange() const { return m_range; }

	inline void setPosition(const glm::vec3& position) { m_position = position; }
	inline void setRange(float range) { m_range = range; }
private:
	glm::vec3 m_position;
	float m_range;
};
