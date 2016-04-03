#pragma once

#include "PointLightComponent.hpp"

class SpotLightComponent : public PointLightComponent {
public:
	SpotLightComponent(const glm::vec3& colour,
					   float luminosity,
					   float range,
					   float cosineFov) : PointLightComponent(colour, luminosity, range),
										  m_cosineFov(cosineFov) { }

	inline float getCosineFov() const { return m_cosineFov; }
	inline void setCosineFov(float cosineFov) { m_cosineFov = cosineFov; }

	virtual void addToEngine(Engine* engine) const;
protected:
	virtual ShadowFramebuffer* generateFrameBuffer() override {
		return nullptr;
	}

	virtual BaseCameraComponent* generateCamera() override {
		return nullptr;
	}
private:
	float m_cosineFov;
};



