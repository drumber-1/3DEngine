#pragma once

#include "BaseLight.hpp"

class DirectionalLight : public BaseLight {
public:
	DirectionalLight(const glm::vec3& colour, float luminosity, const glm::vec3& direction) : BaseLight(colour, luminosity), m_direction(direction) {}

	inline const glm::vec3& getDirection() const { return m_direction; }

	inline void setDirection(glm::vec3 direction) { m_direction = direction; }
private:
	glm::vec3 m_direction;
};
