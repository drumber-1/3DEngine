#pragma once

#include <memory>
#include "BaseFramebuffer.hpp"

class ShadowFramebuffer : public BaseFramebuffer {
public:
	ShadowFramebuffer(int width, int height, float borderIntensity, bool useCubeMap);

	const BaseTextureData* getShadowMap() const { return m_shadowMap.get(); }

private:
	std::unique_ptr<BaseTextureData> m_shadowMap;
	bool m_cubeMap;
};



