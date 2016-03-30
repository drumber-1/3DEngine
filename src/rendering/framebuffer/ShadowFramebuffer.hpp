#pragma once

#include "BaseFramebuffer.hpp"
#include "../texture/DepthTexture2DData.hpp"

class ShadowFramebuffer : public BaseFramebuffer {
public:
	ShadowFramebuffer(int width, int height);

	const DepthTexture2DData& getShadowMap() const { return m_shadowMap; }
private:
	DepthTexture2DData m_shadowMap;
};



