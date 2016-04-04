#pragma once

#include <GL/glew.h>
#include "BaseTextureData.hpp"

class Texture2DData : public BaseTextureData {
public:
	Texture2DData(int width, int height) : BaseTextureData(GL_TEXTURE_2D, width, height) {}
	Texture2DData(int width, int height, const GLvoid* data);
	static Texture2DData* generateShadowMap(int width, int height, float borderIntensity);
};



