#include "TextureList.hpp"

TextureList TextureList::g_textureList;

Texture* TextureList::getAddTexture(const std::string& identifier) {
	size_t n = m_textures.count(identifier);

	if (n == 0) {
		m_textures.emplace(std::make_pair(identifier, Texture(identifier)));
	}

	return &m_textures.find(identifier)->second;
}