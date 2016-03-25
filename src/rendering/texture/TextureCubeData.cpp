//
// Created by jake on 24/03/16.
//

#include "TextureCubeData.hpp"

TextureCubeData::TextureCubeData(int width, int height, const std::array<GLvoid*, 6>& data) : BaseTextureData(GL_TEXTURE_CUBE_MAP, width, height) {
	for (unsigned int i = 0; i < data.size(); ++i) {
		load(data[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
	}
}

