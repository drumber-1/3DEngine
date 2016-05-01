#include "Texture2DData.hpp"

Texture2DData::Texture2DData(int width, int height, const GLvoid* data) : BaseTextureData(GL_TEXTURE_2D, width, height) {
	setParameters(GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, 8.0f);
	load(data, GL_TEXTURE_2D, GL_RGB);
	generateMipmaps();
}

Texture2DData* Texture2DData::generateShadowMap(int width, int height, float borderIntensity) {
	Texture2DData* data = new Texture2DData(width, height);
	data->setAsShadowMap(GL_TEXTURE_2D, borderIntensity);
	return data;
}
