#pragma once

#include <memory>
#include <string>

#include "TextureData.hpp"
#include "../../core/ResourceManager.hpp"

class Texture {
public:
	Texture(const std::string& fileName, bool loadNow = true);

	inline void bind(GLint textureUnit) const { m_textureData->bind(textureUnit); }

	void load();
	inline void unload() { m_textureData.reset(); }
	inline bool isLoaded() const { return m_textureData.get() == nullptr; }

	static ResourceManager<Texture> textureManager;
private:
	std::unique_ptr<TextureData> m_textureData;
	std::string m_fileName;
};



