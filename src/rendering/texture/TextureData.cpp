#include "TextureData.hpp"

#include <iostream>

TextureData::TextureData(GLenum textureType, int width, int height, const GLvoid* data) : m_textureType(textureType),
																						  m_width(width),
																						  m_height(height) {
	glGenTextures(1, &m_textureID);
	glBindTexture(m_textureType, m_textureID);

	if (m_textureType == GL_TEXTURE_2D) { //Load normal 2d texture now, other types (e.g. cubemaps) must be done manually
		TextureData::load(width, height, data, GL_TEXTURE_2D, GL_TEXTURE_2D);
	}

}

void TextureData::bind(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(m_textureType, m_textureID);
}

void TextureData::load(int width, int height, const GLvoid* data, GLenum textureType, GLenum textureTarget) {
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