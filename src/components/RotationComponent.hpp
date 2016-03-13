#pragma once

#include "BaseComponent.hpp"

class RotationComponent : public BaseComponent {
public:
	RotationComponent(float speed, glm::vec3 axis) : m_speed(speed), m_axis(axis) {}
	virtual void update(const Input& input, float delta) {
		getTransform().rotate(delta * m_speed, m_axis);
	}

private:
	float m_speed;
	glm::vec3 m_axis;
};



