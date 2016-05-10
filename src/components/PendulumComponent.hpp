#pragma once

#include <glm/vec3.hpp>
#include <cmath>
#include "BaseComponent.hpp"

class PendulumComponent : public BaseComponent {
public:
	PendulumComponent(glm::vec3 anchor, glm::vec3 start, glm::vec3 axis,
					  float accel,
					  float angle) : m_anchor(anchor),
									 m_axis(axis),
									 m_radial(start - anchor),
									 m_sqrtgl(std::sqrt(accel / std::abs((anchor - start).length()))),
									 m_angleStart(angle) {
	}

	virtual void update(const Input& input, float delta) {
		m_time += delta;
		float new_angle = m_angleStart * std::cos(m_sqrtgl * m_time);
		glm::vec3 newRadial = glm::vec3(glm::vec4(m_radial, 1.0f) * glm::rotate(glm::mat4(), new_angle, m_axis));
		getTransform().setTranslation(m_anchor + newRadial);
		getTransform().setRotation(-new_angle, m_axis);
	}
private:
	const glm::vec3 m_anchor;
	const glm::vec3 m_axis;
	const glm::vec3 m_radial;
	float m_sqrtgl;
	const float m_angleStart;

	float m_time = 0;
};



