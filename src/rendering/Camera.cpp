#include "Camera.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspectRatio) : m_position(0.0f, 0.0f, 0.0f),
				                               m_viewDirection(0.0f, 0.0f, 3.0f),
				                               m_UP(0.0f, 1.0f, 0.0f),
                                               m_fov(fov),
                                               m_aspectRatio(aspectRatio),
											   m_near(0.1f),
											   m_far(100.0f) {
	updateLeft();
}


void Camera::turnLeft(float angle) {
	m_viewDirection = glm::mat3(glm::rotate(glm::mat4(), angle, m_UP)) * m_viewDirection;
	updateLeft();
}
