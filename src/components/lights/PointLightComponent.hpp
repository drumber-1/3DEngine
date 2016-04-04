#pragma once

#include "BaseLightComponent.hpp"
#include "../camera/BaseCameraComponent.hpp"

class PointLightComponent : public BaseLightComponent {
public:
	PointLightComponent(const glm::vec3& colour, float luminosity,
						float range, bool xray = false) : BaseLightComponent(colour, luminosity, xray),
												          m_range(range) {}
	inline float getRange() const { return m_range; }
	inline void setRange(float range) { m_range = range; }

	virtual void addToEngine(Engine* engine) const;
protected:
	virtual ShadowFramebuffer* generateFrameBuffer() override;
	virtual BaseCameraComponent* generateCamera() override;
private:
	float m_range;
};



