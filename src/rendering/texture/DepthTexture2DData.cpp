#include "DepthTexture2DData.hpp"

DepthTexture2DData::DepthTexture2DData(int width, int height, bool defaultShadow) : BaseTextureData(GL_TEXTURE_2D, width, height) {
	if (defaultShadow) {
		GLfloat borderColour[] = {0.0, 0.0, 0.0, 1.0};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
	} else {
		GLfloat borderColour[] = {1.0, 1.0, 1.0, 1.0};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
	}
	load(nullptr, GL_TEXTURE_2D, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_BORDER, 0.0f);
}