#pragma once

#include "../BaseComponent.hpp"

class BaseCameraComponent : public BaseComponent {
public:
	virtual glm::mat4 getViewToProjection() const = 0;

	inline glm::mat4 getWorldToViewMatrix() const { return getCameraMatrix(); }

	inline glm::mat4 getWorldToProjectionMatrix() const { return getViewToProjection() * getWorldToViewMatrix(); }

	virtual float getFarPlane() const = 0;
};
