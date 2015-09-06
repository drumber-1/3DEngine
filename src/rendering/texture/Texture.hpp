#pragma once

#include <memory>
#include <string>

#include "TextureData.hpp"

class Texture {
public:
	Texture(const std::string& fileName, bool loadNow = true);

	inline void bind() const { m_textureData->bind(); }

	void load();
	inline void unload() { m_textureData.reset(); }
	inline bool isLoaded() const { return m_textureData.get() == nullptr; }
private:
	std::unique_ptr<TextureData> m_textureData;
	std::string m_fileName;
};



