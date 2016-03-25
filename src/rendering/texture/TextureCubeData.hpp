#pragma once

#include <GL/glew.h>
#include <array>
#include "BaseTextureData.hpp"

class TextureCubeData : public BaseTextureData {
public:
	TextureCubeData(int width, int height, const std::array<GLvoid*, 6>& data);
};



