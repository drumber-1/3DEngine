#pragma once

#include <memory>
#include "BaseFramebuffer.hpp"

class FrameBuffer : public BaseFramebuffer {
public:
	FrameBuffer(int width, int height, bool useCubeMap);

	inline const BaseTextureData* getTextureData() const {
		return m_colourData.get();
	}

	void bindWithDirection(unsigned int dir) const {
		bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + dir, m_colourData.get()->getID(), 0);
	}
private:
	std::unique_ptr<BaseTextureData> m_colourData;
	std::unique_ptr<Renderbuffer> m_depthData;
	bool m_cubeMap;
};



