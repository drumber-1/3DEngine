#pragma once

#include "BaseLightComponent.hpp"
#include "../camera/BaseCameraComponent.hpp"
#include "Attenuation.hpp"

class PointLightComponent : public BaseLightComponent {
public:
	PointLightComponent(const glm::vec3& colour,
						float luminosity,
						float range) : BaseLightComponent(colour, luminosity, false),
									   m_range(range) { }

	PointLightComponent(const glm::vec3& colour,
						float luminosity,
						float range,
						Attenuation attenuation,
						bool xray) : BaseLightComponent(colour, luminosity, xray),
									 m_range(range),
									 m_attenuation(attenuation) { }

	inline float getRange() const { return m_range; }

	inline const Attenuation& getAttenuation() const { return m_attenuation; }

	virtual void addToWorld(GameWorld* world) const override;

protected:
	virtual ShadowFramebuffer* generateFrameBuffer() override;

	virtual BaseCameraComponent* generateCamera() override;

private:
	float m_range;
	Attenuation m_attenuation;
};



