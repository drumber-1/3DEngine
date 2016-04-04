#include <iostream>
#include "ShadowFramebuffer.hpp"
#include "../texture/Texture2DData.hpp"

ShadowFramebuffer::ShadowFramebuffer(int width, int height, float borderIntensity) : BaseFramebuffer(width, height) {
	m_shadowMap.reset(new Texture2DData(width, height, nullptr, true, borderIntensity));
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.get()->getID(), 0);
}