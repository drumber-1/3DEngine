#pragma once

#include "PointLightComponent.hpp"

class SpotLightComponent : public PointLightComponent {
public:
	SpotLightComponent(const glm::vec3& colour,
					   float luminosity,
					   float range,
					   float cosineFov) : PointLightComponent(colour, luminosity, range),
										  m_cosineFov(cosineFov) { }

	SpotLightComponent(const glm::vec3& colour,
					   float luminosity,
					   float range,
					   float cosineFov,
					   Attenuation attenuation,
					   bool xray = false) : PointLightComponent(colour, luminosity, range, attenuation, xray),
											m_cosineFov(cosineFov) { }

	inline float getCosineFov() const { return m_cosineFov; }

	virtual void addToEngine(Engine* engine) const;

protected:
	virtual ShadowFramebuffer* generateFrameBuffer() override;

	virtual BaseCameraComponent* generateCamera() override;

private:
	float m_cosineFov;
};



