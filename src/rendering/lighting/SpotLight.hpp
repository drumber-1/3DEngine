#pragma once

#include "PointLight.hpp"

class SpotLight : public PointLight {
public:
	SpotLight(const glm::vec3& colour,
			  float luminosity,
			  const glm::vec3& position,
			  float range,
			  const glm::vec3& direction,
			  float cosineFov) : PointLight(colour, luminosity, position, range),
								 m_direction(direction),
								 m_cosineFov(cosineFov) {}
	inline const glm::vec3& getDirection() const { return m_direction; }
	inline float getCosineFov() const { return m_cosineFov; }

	inline void setDirection(const glm::vec3& direction) { m_direction = direction; }
	inline void setCosineFov(float cosineFov) { m_cosineFov = cosineFov; }
private:
	glm::vec3 m_direction;
	float m_cosineFov;
};



