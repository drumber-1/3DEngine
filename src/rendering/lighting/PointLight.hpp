#pragma once

#include "BaseLight.hpp"

class PointLight : public BaseLight {
public:
	PointLight(const glm::vec3& colour, float luminosity, const glm::vec3& position) : BaseLight(colour, luminosity), m_position(position) {}

	inline const glm::vec3& getPosition() const { return m_position; }

	inline void setPosition(const glm::vec3& position) { m_position = position; }
private:
	glm::vec3 m_position;
};
