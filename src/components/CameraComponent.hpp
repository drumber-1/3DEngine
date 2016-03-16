#pragma once

#include "BaseComponent.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class CameraComponent : public BaseComponent {
public:
	CameraComponent(float fov, float aspectRatio) : m_fov(fov),
													m_aspectRatio(aspectRatio),
													m_near(0.1f),
													m_far(100.0f) {
	}

	inline glm::mat4 getWorldToViewMatrix() const { return getCameraMatrix(); }
	inline glm::mat4 getViewToProjection() const { return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far); }
	inline glm::mat4 getWorldToProjectionMatrix() const { return getViewToProjection() * getWorldToViewMatrix(); }

	inline float getFov() const { return m_fov; }
	inline float getAspectRatio() const { return m_aspectRatio; }

	inline void setFov(float fov) { m_fov = fov; }
	inline void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

private:
	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;
};



