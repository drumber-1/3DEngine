#include "Texture.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ResourceManager<Texture> Texture::textureManager;
std::array<std::string, 6> cubemapSuffixes = {"/right.jpg", "/left.jpg", "/top.jpg", "/bottom.jpg", "/back.jpg", "/front.jpg"};

Texture::Texture(const std::string& filename, bool loadNow) : m_filename(filename) {
	if (filename.find("cube") == 0) {
		m_textureType = GL_TEXTURE_CUBE_MAP;
	} else {
		m_textureType = GL_TEXTURE_2D;
	}
	if (loadNow) {
		load();
	}
}

void Texture::load() {
	if (m_textureType == GL_TEXTURE_CUBE_MAP) {
		for (unsigned int i = 0; i < 6; i++) {
			std::string filenameFull = m_filename + cubemapSuffixes[i];
			SDL_Surface* surface = IMG_Load(("res/textures/" + filenameFull).c_str());
			if (surface == nullptr) {
				std::cerr << "Unable to load image from " << filenameFull << ", SDL_image Error: " << IMG_GetError() <<
				"\n";
				return;
			}
			if (i == 0) {
				textureData.reset(new TextureData(GL_TEXTURE_CUBE_MAP, surface->w, surface->h, nullptr));
			}
			textureData->load(surface->w, surface->h, surface->pixels, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			SDL_FreeSurface(surface);
		}
	} else {
		SDL_Surface* surface = IMG_Load(("res/textures/" + m_filename).c_str());
		if (surface == nullptr) {
			std::cerr << "Unable to load image from " << m_filename << ", SDL_image Error: " << IMG_GetError() <<
			"\n";
			return;
		}
		textureData.reset(new TextureData(GL_TEXTURE_2D, surface->w, surface->h, surface->pixels));
		SDL_FreeSurface(surface);
	}
}

void Texture::bind(GLenum textureUnit) const {
	textureData->bind(textureUnit);
}
