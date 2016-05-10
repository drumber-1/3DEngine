#pragma once

#include <glm/vec3.hpp>
#include "BaseComponent.hpp"

class OrbitComponent : public BaseComponent {
public:
	OrbitComponent(glm::vec3 centre, glm::vec3 axis,
				   float speed, float radius, float start = 0) : m_centre(centre), m_axis(axis), m_radial(glm::cross(m_axis, glm::vec3(1, 0, 0))),
																 m_speed(speed), m_radius(radius), m_current(start) {
	}

	virtual void update(const Input& input, float delta) {
		m_current += m_speed * delta;
		m_rotation = glm::rotate(glm::mat4(), m_current, m_axis);
		glm::rotate(m_rotation, m_speed * delta, m_axis);
		glm::vec3 newRadial = glm::vec3(glm::vec4(m_radial, 1.0f) * m_rotation);
		getTransform().setTranslation(m_centre + newRadial);
	}
private:
	const glm::vec3 m_centre;
	const glm::vec3 m_axis;
	const glm::vec3 m_radial;
	const float m_speed;
	const float m_radius;
	float m_current;
	glm::mat4 m_rotation;
};



