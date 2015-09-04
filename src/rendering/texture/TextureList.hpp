#pragma once

#include <string>
#include <unordered_map>

#include "Texture.hpp"

class TextureList {
public:
	void add(const std::string& fileName) { m_textures.emplace(std::make_pair(fileName, Texture(fileName))); }

	void bind(const std::string& identifier) const { getTexture(identifier).bind(); }

	void load(const std::string& identifier) { getTexture(identifier).load(); }
	void unload(const std::string& identifier) { getTexture(identifier).unload(); }
	bool isLoaded(const std::string& identifier) const { return getTexture(identifier).isLoaded(); }

	const Texture& getTexture(const std::string& identifier) const { return m_textures.find(identifier)->second; }
	Texture& getTexture(const std::string& identifier) { return m_textures.find(identifier)->second; }
	Texture* getAddTexture(const std::string& identifier);

	static TextureList g_textureList;
	static Texture* getAddTextureGlobal(const std::string& identifier) { return g_textureList.getAddTexture(identifier); }
private:
	std::unordered_map<std::string, Texture> m_textures;
};



