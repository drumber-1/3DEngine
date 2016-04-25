#pragma once

#include "BaseFramebuffer.hpp"

class FrameBuffer : public BaseFramebuffer {
public:
	FrameBuffer(int width, int height, bool useCubeMap);
private:
	std::unique_ptr<BaseTextureData> m_colourData;
	std::unique_ptr<Renderbuffer> m_depthData;
	bool m_cubeMap;
};



