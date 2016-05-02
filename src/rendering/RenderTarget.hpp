#pragma once

#include "../components/camera/BaseCameraComponent.hpp"
#include "framebuffer/FrameBuffer.hpp"
#include "../components/camera/CubeCameraComponent.hpp"

class RenderTarget {
public:
	RenderTarget(int width, int height, CubeCameraComponent* camera, int renderFreq) : m_framebuffer(width, height, true),
																			           m_camera(camera),
																					   m_renderFreq(renderFreq) {
		if (m_renderFreq <= 0) {
			m_renderFreq = 0;
		}
	}

	bool shouldRender() {
		m_lastRender++;
		if (m_lastRender >= m_renderFreq) {
			m_lastRender = 0;
			return true;
		} else {
			return false;
		}
	}

	inline const CubeCameraComponent* getCamera() const {
		return m_camera;
	}

	inline void bindAsRenderTarget(unsigned int dir) const {
		m_framebuffer.bindWithDirection(dir);
		m_camera->setDirection(dir);
	}

	const BaseTextureData* getTextureData() const {
		return m_framebuffer.getTextureData();
	}
private:
	FrameBuffer m_framebuffer;
	CubeCameraComponent* m_camera;
	int m_renderFreq;
	int m_lastRender = 0;
};



