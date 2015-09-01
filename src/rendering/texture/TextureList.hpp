#pragma once

#include <string>
#include <unordered_map>

#include "Texture.hpp"

class TextureList {
public:
	void add(std::string identifier, const std::string& fileName) { m_textures.emplace(std::make_pair(identifier, Texture(fileName))); }

	void bind(const std::string& identifier) const { getTexture(identifier).bind(); }

	void load(const std::string& identifier) { getTexture(identifier).load(); }
	void unload(const std::string& identifier) { getTexture(identifier).unload(); }
	bool isLoaded(const std::string& identifier) const { return getTexture(identifier).isLoaded(); }

	const Texture& getTexture(const std::string& identifier) const { return m_textures.find(identifier)->second; }
	Texture& getTexture(const std::string& identifier) { return m_textures.find(identifier)->second; }
private:
	std::unordered_map<std::string, Texture> m_textures;
};



