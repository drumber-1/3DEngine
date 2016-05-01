#pragma once

#include <array>

#include "PerspectiveCameraComponent.hpp"

class CubeCameraComponent : public PerspectiveCameraComponent {

public:
	CubeCameraComponent(float fov, float aspectRatio) : PerspectiveCameraComponent(fov, aspectRatio) { }

	glm::mat4 getWorldToViewMatrix(int i) const {
		return glm::lookAt(getPosition(), getPosition() + getDir(i), getUp(i));
	}

	glm::mat4 getWorldToProjectionMatrix(int i) const {
		return getViewToProjection() * getWorldToViewMatrix(i);
	}

	glm::mat4 getWorldToViewMatrix() const {
		return getWorldToViewMatrix(m_currentDir);
	}

	glm::mat4 getWorldToProjectionMatrix() const {
		return getWorldToProjectionMatrix(m_currentDir);
	}

	inline void setDirection(int i) { m_currentDir = i; }
private:
	static const glm::vec3& getDir(int i) {
		static const std::array<glm::vec3, 6> DIRS = {glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0),
													  glm::vec3(0.0, 1.0, 0.0), glm::vec3( 0.0,-1.0, 0.0),
													  glm::vec3(0.0, 0.0, 1.0), glm::vec3( 0.0, 0.0,-1.0)};
		return DIRS[i];
	};

	static const glm::vec3& getUp(int i) {
		static const std::array<glm::vec3, 6> UPS = {glm::vec3(0.0,-1.0, 0.0), glm::vec3( 0.0,-1.0, 0.0),
													 glm::vec3(0.0, 0.0, 1.0), glm::vec3( 0.0, 0.0,-1.0),
													 glm::vec3(0.0,-1.0, 0.0), glm::vec3( 0.0,-1.0, 0.0)};
		return UPS[i];
	};

	int m_currentDir = 0;
};
