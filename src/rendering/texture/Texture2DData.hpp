#pragma once

#include <GL/glew.h>
#include "BaseTextureData.hpp"

class Texture2DData : public BaseTextureData {
public:
	Texture2DData(int width, int height, const GLvoid* data);
};



