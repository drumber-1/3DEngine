#pragma once

#include "BaseCameraComponent.hpp"

class PerspectiveCameraComponent : public BaseCameraComponent {
public:
	PerspectiveCameraComponent(float fov, float aspectRatio) : m_fov(fov),
															   m_aspectRatio(aspectRatio),
															   m_near(0.1f), m_far(100.0f) { }

	virtual glm::mat4 getViewToProjection() const {
		return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	inline float getFov() const { return m_fov; }

	inline float getAspectRatio() const { return m_aspectRatio; }

	inline void setFov(float fov) { m_fov = fov; }

	inline void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

private:
	float m_fov;
	float m_aspectRatio;
	const float m_near, m_far;
};