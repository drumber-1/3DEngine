#include <iostream>
#include "Framebuffer.hpp"

Framebuffer::Framebuffer(int width, int height) : m_width(width), m_height(height) {
	glGenFramebuffers(1, &m_framebufferID);

	m_colourData.reset(new BaseTextureData(GL_TEXTURE_2D, m_width, m_height));
	m_colourData->load(nullptr, GL_TEXTURE_2D, GL_RGB, GL_LINEAR, GL_REPEAT, 0.0f);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourData->getID(), 0);

	m_depthData.reset(new Renderbuffer(GL_DEPTH, m_width, m_height));
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthData->getID());

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::Framebuffer:: Framebuffer is not complete!\n";
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind() {
	glViewport(0, 0, m_width, m_height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
}

void Framebuffer::unbindAll() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
