#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class CameraProjection {
public:
	CameraProjection(float fov, float aspectRatio, float near, float far) : m_fov(fov),
																			m_aspectRatio(aspectRatio),
																			m_near(near),
																			m_far(far) {}
	inline glm::mat4 getViewToProjection() const { return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far); }
private:
	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;
};



