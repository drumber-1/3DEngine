#pragma once

#include <string>
#include <array>
#include <GL/glew.h>
#include <bits/unique_ptr.h>

#include "../../core/ResourceManager.hpp"
#include "TextureData.hpp"

class Texture {
public:
	Texture(const std::string& filename, bool loadNow = true);

	void bind(GLenum textureUnit) const;

	void load();
	inline void unload() { textureData.reset(); }

	static ResourceManager<Texture> textureManager;
private:
	const std::string m_filename;
	std::unique_ptr<TextureData> textureData;
	GLenum m_textureType;
};



