#pragma once

#include "../BaseComponent.hpp"
#include "../../rendering/framebuffer/ShadowFramebuffer.hpp"
#include "../camera/BaseCameraComponent.hpp"

class BaseLightComponent : public BaseComponent {
public:
	BaseLightComponent(const glm::vec3& colour, float luminosity, bool xray) : m_colour(colour),
																	m_luminosity(luminosity),
																	m_xray(xray) {}

	inline const glm::vec3& getColour() const { return m_colour; }
	inline void setColour(const glm::vec3& colour) { m_colour = colour; }

	inline float getLuminosity() const { return m_luminosity; }
	inline void setLuminosity(float luminosity) { m_luminosity = luminosity; }

	inline bool isXray() const { return m_xray; }

	const ShadowFramebuffer* getShadowMapBuffer() const { return m_shadowMapBuffer.get(); };
	const BaseCameraComponent* getCamera() const { return m_Camera; };
protected:
	virtual ShadowFramebuffer* generateFrameBuffer() = 0;
	virtual BaseCameraComponent* generateCamera() = 0;

	virtual void setParentEntity(Entity* parent) override {
		BaseComponent::setParentEntity(parent);
		if (!m_xray) {
			m_shadowMapBuffer.reset(generateFrameBuffer());
			m_Camera = generateCamera();
			parent->addComponent(m_Camera);
		}
	}

private:
	glm::vec3 m_colour;
	float m_luminosity;

	const bool m_xray;
	//It is not strictly necessary to have a buffer and a camera for every light, however it makes it simpler
	// in the renderer and allows each light to have different resolutions, areas of effect etc
	std::unique_ptr<ShadowFramebuffer> m_shadowMapBuffer;
	BaseCameraComponent* m_Camera; // This will be owned by the parent entity, so only keep a raw pointer
};



