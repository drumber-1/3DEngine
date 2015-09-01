#pragma once

#include <memory>
#include <string>

#include "TextureData.hpp"

class Texture {
public:
	Texture(const std::string& fileName, bool loadNow = true);
	void bind() const;

	void load();
	void unload();
	bool isLoaded() const;
private:
	std::unique_ptr<TextureData> m_textureData;
	std::string m_fileName;
};



