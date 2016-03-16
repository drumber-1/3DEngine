#include "Texture.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ResourceManager<Texture> Texture::textureManager;
std::array<std::string, 6> cubemapSuffixes = {"/right.jpg", "/left.jpg", "/top.jpg", "/bottom.jpg", "/back.jpg", "/front.jpg"};

void textureLoader(int width, int height, const GLvoid* data, GLenum textureType, GLenum textureTarget) {
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(textureType);
	GLfloat maxAnisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, std::min(8.0f, maxAnisotropy));

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Texture::Texture(const std::string& filename, bool loadNow) : m_filename(filename) {
	glGenTextures(1, &m_textureID);
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
	glBindTexture(m_textureType, m_textureID);
	if (m_textureType == GL_TEXTURE_CUBE_MAP) {
		for (unsigned int i = 0; i < 6; i++) {
			std::string filenameFull = m_filename + cubemapSuffixes[i];
			SDL_Surface* surface = IMG_Load(("res/textures/" + filenameFull).c_str());
			if (surface == nullptr) {
				std::cerr << "Unable to load image from " << filenameFull << ", SDL_image Error: " << IMG_GetError() <<
				"\n";
				continue;
				//return;
			}
			textureLoader(surface->w, surface->h, surface->pixels, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			SDL_FreeSurface(surface);
		}
	} else {
		SDL_Surface* surface = IMG_Load(("res/textures/" + m_filename).c_str());
		if (surface == nullptr) {
			std::cerr << "Unable to load image from " << m_filename << ", SDL_image Error: " << IMG_GetError() <<
			"\n";
			return;
		}
		textureLoader(surface->w, surface->h, surface->pixels, GL_TEXTURE_2D, GL_TEXTURE_2D);
		SDL_FreeSurface(surface);
	}
}

void Texture::bind(GLint textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(m_textureType, m_textureID);
}
