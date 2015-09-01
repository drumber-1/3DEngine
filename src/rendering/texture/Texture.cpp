#include "Texture.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::Texture(const std::string &fileName, bool loadNow) : m_fileName(fileName) {
	if (loadNow) {
		load();
	}
}

void Texture::bind() const {
	m_textureData->bind();
}

void Texture::load() {
	SDL_Surface* surface = IMG_Load(("res/textures/" + m_fileName).c_str());
	if (surface == nullptr) {
		std::cerr << "Unable to load image from " << m_fileName << ", SDL_image Error: " << IMG_GetError() << "\n";
		return;
	}
	m_textureData.reset(new TextureData(surface->w, surface->h, surface->pixels));
	SDL_FreeSurface(surface);
}

void Texture::unload() {
	m_textureData.reset();
}

bool Texture::isLoaded() const {
	return m_textureData.get() == nullptr;
}
