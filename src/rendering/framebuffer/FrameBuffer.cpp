#include "FrameBuffer.hpp"
#include "../texture/TextureCubeData.hpp"
#include "../texture/Texture2DData.hpp"

FrameBuffer::FrameBuffer(int width, int height, bool useCubeMap) : BaseFramebuffer(width, height), m_cubeMap(useCubeMap) {
	if (useCubeMap) {
		m_colourData.reset(new TextureCubeData(width, height));
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colourData.get()->getID(), 0);
		m_depthData.reset(new Renderbuffer(GL_DEPTH_COMPONENT24, width, height));
	} else {
		m_colourData.reset(new Texture2DData(width, height));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourData.get()->getID(), 0);
		m_depthData.reset(new Renderbuffer(GL_DEPTH_COMPONENT24, width, height));
	}
}

