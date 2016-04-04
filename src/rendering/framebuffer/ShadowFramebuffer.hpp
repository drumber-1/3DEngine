#pragma once

#include "BaseFramebuffer.hpp"

class ShadowFramebuffer : public BaseFramebuffer {
public:
	ShadowFramebuffer(int width, int height, float borderIntensity);

	const BaseTextureData* getShadowMap() const { return m_shadowMap.get(); }

private:
	std::unique_ptr<BaseTextureData> m_shadowMap;
};



