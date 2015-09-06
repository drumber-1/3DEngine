#pragma once

#include "BaseLight.hpp"

class DirectionalLight : public BaseLight {
public:
	DirectionalLight(glm::vec3 colour, float luminosity, glm::vec3 direction) : BaseLight(colour, luminosity), m_direction(direction) {}

	const glm::vec3& getDirection() const { return m_direction; }
	glm::vec3& getDirection() { return m_direction; }

	void setDirection(glm::vec3 direction) { m_direction = direction; }
private:
	glm::vec3 m_direction;
};
