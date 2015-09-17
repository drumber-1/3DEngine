#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(float fov, float aspectRatio);

	inline void move(const glm::vec3& delta) { m_position += delta; }
	inline void move(const glm::vec3& dir, float distance) { move(dir * distance); }
	inline void moveForward(float distance) { move(m_viewDirection, distance); }
	inline void moveLeft(float distance) { move(m_left, distance); }
	inline void moveUp(float distance) { move(m_UP, distance); }

	inline void turnUp(float angle) { m_viewDirection = glm::mat3(glm::rotate(glm::mat4(), angle, m_left)) * m_viewDirection; }
	void turnLeft(float angle);

	inline glm::mat4 getWorldToViewMatrix() const { return glm::lookAt(m_position, m_position + m_viewDirection, m_UP); }
	inline glm::mat4 getViewToProjection() const { return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far); }
	inline glm::mat4 getWorldToProjectionMatrix() const { return getViewToProjection() * getWorldToViewMatrix(); }
	inline const glm::vec3& getPosition() const { return m_position; }
	inline const glm::vec3& getViewDirection() const { return m_viewDirection; }
	inline float getFov() const { return m_fov; }
	inline float getAspectRatio() const { return m_aspectRatio; }

	inline void setPosition(const glm::vec3& pos) { m_position = pos; }
	inline void setViewDirection(const glm::vec3& dir) { m_viewDirection = glm::normalize(dir); }
	inline void setFov(float fov) { m_fov = fov; }
	inline void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }

private:
	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	glm::vec3 m_left;
	const glm::vec3 m_UP;

	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;

	inline void updateLeft() { m_left = glm::cross(m_UP, m_viewDirection); }
};



