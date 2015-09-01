#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();

	inline void move(glm::vec3 delta) { m_position += delta; }
	inline void move(glm::vec3 dir, float distance) { move(dir * distance); }
	inline void moveForward(float distance) { move(m_viewDirection, distance); }
	inline void moveLeft(float distance) { move(m_left, distance); }
	inline void moveUp(float distance) { move(m_UP, distance); }

	inline void turnUp(float angle) { m_viewDirection = glm::mat3(glm::rotate(glm::mat4(), angle, m_left)) * m_viewDirection; }
	void turnLeft(float angle);

	inline glm::mat4 getWorldToViewMatrix() const { return glm::lookAt(m_position, m_position + m_viewDirection, m_UP); }

	inline void setPosition(glm::vec3 pos) { m_position = pos; }
	inline void setViewDirection(glm::vec3 dir) { m_viewDirection = glm::normalize(dir); }
private:
	glm::vec3 m_position;
	glm::vec3 m_viewDirection;
	glm::vec3 m_left;
	const glm::vec3 m_UP;

	inline void updateLeft() { m_left = glm::cross(m_UP, m_viewDirection); }
};



