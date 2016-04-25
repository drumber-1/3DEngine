#include <iostream>
#include "ShadowFramebuffer.hpp"
#include "../texture/Texture2DData.hpp"
#include "../texture/TextureCubeData.hpp"

ShadowFramebuffer::ShadowFramebuffer(int width, int height, float borderIntensity, bool useCubeMap) : BaseFramebuffer(width, height),
																									  m_cubeMap(useCubeMap) {
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (useCubeMap) {
		m_shadowMap.reset(TextureCubeData::generateShadowCube(width, height, borderIntensity));
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMap.get()->getID(), 0);
	} else {
		m_shadowMap.reset(Texture2DData::generateShadowMap(width, height, borderIntensity));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.get()->getID(), 0);
	}
}