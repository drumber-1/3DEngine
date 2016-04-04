#include <algorithm>
#include "BaseTextureData.hpp"

BaseTextureData::BaseTextureData(GLenum textureType, int width, int height)  : m_textureType(textureType),
																			   m_width(width),
																			   m_height(height) {
	glGenTextures(1, &m_textureID);
	glBindTexture(m_textureType, m_textureID);
}

void BaseTextureData::bind(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(m_textureType, m_textureID);
}

void BaseTextureData::load(const GLvoid* data, GLenum textureTarget) {
	bind(GL_TEXTURE0);
	load(data, textureTarget, GL_RGB, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, 8.0f);
}

void BaseTextureData::loadAsShadowMap(GLenum textureTarget, float borderIntensity) {
	bind(GL_TEXTURE0);
	GLfloat borderColour[] = {borderIntensity, borderIntensity, borderIntensity, 1.0};
	glTexParameterfv(m_textureType, GL_TEXTURE_BORDER_COLOR, borderColour);
	load(nullptr, textureTarget, GL_DEPTH_COMPONENT, GL_NEAREST, GL_CLAMP_TO_BORDER, 0.0f);
}

void BaseTextureData::load(const GLvoid* data, GLenum textureTarget, GLenum format, GLint interpolation, GLint wrapping, float anisotropy) {
	bind(GL_TEXTURE0);
	glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, interpolation);
	glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, interpolation);

	glTexImage2D(textureTarget, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

	if (interpolation == GL_NEAREST_MIPMAP_NEAREST || interpolation == GL_NEAREST_MIPMAP_LINEAR ||
		interpolation == GL_LINEAR_MIPMAP_NEAREST || interpolation == GL_LINEAR_MIPMAP_LINEAR) {
		glGenerateMipmap(m_textureType);
	}

	if (anisotropy > 0) {
		GLfloat maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(m_textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, std::min(anisotropy, maxAnisotropy));
	}

	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_R, wrapping);
}





