#pragma once

#include <string>
#include <array>
#include <GL/glew.h>
#include <bits/unique_ptr.h>

#include "../../core/ResourceManager.hpp"
#include "BaseTextureData.hpp"

class Texture {
public:
	Texture(const std::string& filename, bool loadNow = true);

	void bind(GLenum textureUnit) const;

	void load();
	inline void unload() { textureData.reset(); }

	static ResourceManager<Texture> textureManager;
private:
	const std::string m_filename;
	std::unique_ptr<BaseTextureData> textureData;
	GLenum m_textureType;
};



