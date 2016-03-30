#include <iostream>
#include "ShadowFramebuffer.hpp"

ShadowFramebuffer::ShadowFramebuffer(int width, int height) : BaseFramebuffer(width, height), m_shadowMap(width, height) {
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.getID(), 0);
}