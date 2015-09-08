#pragma once

#include <glm/glm.hpp>

struct BaseLight {
public:
	BaseLight(const glm::vec3& colour, float luminosity) : m_colour(colour), m_luminosity(luminosity) {}

	inline const glm::vec3& getColour() const { return m_colour; }
	inline glm::vec3& getColour() { return m_colour; }
	inline float getLuminosity() const { return m_luminosity; }

	inline void setColour(const glm::vec3& colour) { m_colour = colour; }
	inline void setLuminosity(float luminosity) { m_luminosity = luminosity; }
private:
	glm::vec3 m_colour;
	float m_luminosity;
};



