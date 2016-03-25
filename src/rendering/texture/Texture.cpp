#include "Texture.hpp"
#include "Texture2DData.hpp"
#include "TextureCubeData.hpp"

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
		std::array<SDL_Surface*, 6> surfaces;
		std::array<void*, 6> pixels;
		for (unsigned int i = 0; i < 6; i++) {
			std::string filenameFull = m_filename + cubemapSuffixes[i];
			surfaces[i] = IMG_Load(("res/textures/" + filenameFull).c_str());
			if (surfaces[i] == nullptr) {
				std::cerr << "Unable to load image from " << filenameFull << ", SDL_image Error: " << IMG_GetError() <<
				"\n";
				return;
			}
			pixels[i] = surfaces[i]->pixels;
		}
		textureData.reset(new TextureCubeData(surfaces[0]->w, surfaces[1]->h, pixels));
		for (unsigned int i = 0; i < 6; i++) {
			SDL_FreeSurface(surfaces[i]);
		}
	} else {
		SDL_Surface* surface = IMG_Load(("res/textures/" + m_filename).c_str());
		if (surface == nullptr) {
			std::cerr << "Unable to load image from " << m_filename << ", SDL_image Error: " << IMG_GetError() <<
			"\n";
			return;
		}
		textureData.reset(new Texture2DData(surface->w, surface->h, surface->pixels));
		SDL_FreeSurface(surface);
	}
}

void Texture::bind(GLenum textureUnit) const {
	textureData->bind(textureUnit);
}
