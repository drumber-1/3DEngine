#include "Texture2DData.hpp"

Texture2DData::Texture2DData(int width, int height, const GLvoid* data) : BaseTextureData(GL_TEXTURE_2D, width,
																						  height) {
	load(data, GL_TEXTURE_2D);
}

Texture2DData* Texture2DData::generateShadowMap(int width, int height, float borderIntensity) {
	Texture2DData* data = new Texture2DData(width, height);
	data->loadAsShadowMap(GL_TEXTURE_2D, borderIntensity);
	return data;
}



