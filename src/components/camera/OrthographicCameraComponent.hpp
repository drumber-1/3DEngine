#pragma once

#include "BaseCameraComponent.hpp"

class OrthographicCameraComponent : public BaseCameraComponent {
public:
	OrthographicCameraComponent(float xMin, float xMax, float yMin, float yMax) : m_xMin(xMin), m_xMax(xMax),
																				  m_yMin(yMin), m_yMax(yMax),
																				  m_near(-10.0f), m_far(10.0f) { }

	virtual glm::mat4 getViewToProjection() const {
		return glm::ortho(m_xMin, m_xMax, m_yMin, m_yMax, m_near, m_far);
	}

	virtual float getFarPlane() const {
		return m_far;
	}

private:
	const float m_xMin, m_xMax, m_yMin, m_yMax;
	const float m_near, m_far;
};



