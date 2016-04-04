#include "Texture2DData.hpp"

Texture2DData::Texture2DData(int width, int height, const GLvoid* data) : BaseTextureData(GL_TEXTURE_2D, width,
																						  height) {
	load(data, GL_TEXTURE_2D);
}

Texture2DData::Texture2DData(int width, int height, const GLvoid* data, bool shadowMap, float borderIntensity)
		: BaseTextureData(GL_TEXTURE_2D, width, height) {
	if (shadowMap) {
		loadAsShadowMap(GL_TEXTURE_2D, borderIntensity);
	} else {
		load(data, GL_TEXTURE_2D);
	}
}


