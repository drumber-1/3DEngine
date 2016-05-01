#include "TextureCubeData.hpp"

TextureCubeData::TextureCubeData(int width, int height,
								 const std::array<GLvoid*, 6>& data) : BaseTextureData(GL_TEXTURE_CUBE_MAP, width, height) {
	setParameters(GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, 8.0f);
	for (unsigned int i = 0; i < data.size(); ++i) {
		load(data[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, GL_RGB);
	}
	generateMipmaps();
}

TextureCubeData* TextureCubeData::generateShadowCube(int width, int height, float borderIntensity) {
	TextureCubeData* data = new TextureCubeData(width, height);
	for (unsigned int i = 0; i < 6; ++i) {
		data->setAsShadowMap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, borderIntensity);
	}
	return data;
}

TextureCubeData* TextureCubeData::generateEmptyCube(int width, int height) {
	TextureCubeData* data = new TextureCubeData(width, height);
	data->setParameters(GL_LINEAR, GL_CLAMP_TO_EDGE, 8.0f);
	for (unsigned int i = 0; i < 6; ++i) {
		data->load(nullptr, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, GL_RGB);
	}
	return data;
}