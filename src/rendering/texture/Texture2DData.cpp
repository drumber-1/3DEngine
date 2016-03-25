#include "Texture2DData.hpp"

Texture2DData::Texture2DData(int width, int height, const GLvoid* data) : BaseTextureData(GL_TEXTURE_2D, width, height) {
	load(data, GL_TEXTURE_2D);
}
