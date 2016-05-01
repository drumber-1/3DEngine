#include <algorithm>
#include "BaseTextureData.hpp"
#include "../CheckGLError.hpp"

BaseTextureData::BaseTextureData(GLenum textureType, int width, int height) : m_textureType(textureType),
																			  m_width(width),
																			  m_height(height) {
	glGenTextures(1, &m_textureID);
	glBindTexture(m_textureType, m_textureID);
}

void BaseTextureData::bind(GLenum textureUnit) const {
	glActiveTexture(textureUnit);
	glBindTexture(m_textureType, m_textureID);
}

void BaseTextureData::setParameters(GLint interpolation, GLint wrapping, float anisotropy) {
	bind(GL_TEXTURE0);
	glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, interpolation);
	if (interpolation == GL_NEAREST_MIPMAP_NEAREST ||
		interpolation == GL_LINEAR_MIPMAP_NEAREST ||
		interpolation == GL_NEAREST) {
		glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	} else {
		glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void BaseTextureData::load(const GLvoid* data, GLenum textureTarget, GLenum format) {
	bind(GL_TEXTURE0);
	glTexImage2D(textureTarget, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
}

void BaseTextureData::generateMipmaps() {
	glGenerateMipmap(m_textureType);
}

/*void BaseTextureData::load(const GLvoid* data, GLenum textureTarget) {
	bind(GL_TEXTURE0);
	load(data, textureTarget, GL_RGB, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, 8.0f);
}*/

void BaseTextureData::setAsShadowMap(GLenum textureTarget, float borderIntensity) {
	bind(GL_TEXTURE0);
	GLfloat borderColour[] = {borderIntensity, borderIntensity, borderIntensity, 1.0};
	glTexParameterfv(m_textureType, GL_TEXTURE_BORDER_COLOR, borderColour);
	setParameters(GL_NEAREST, GL_CLAMP_TO_BORDER, 0.0f);
	load(nullptr, textureTarget, GL_DEPTH_COMPONENT);
}

/*void BaseTextureData::load(const GLvoid* data, GLenum textureTarget, GLenum format, GLint interpolation, GLint wrapping,
						   float anisotropy) {
	CheckGLError::checkError("basetexture data start load");
	bind(GL_TEXTURE0);
	CheckGLError::checkError("basetexture data 1");
	glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, interpolation);
	if (interpolation == GL_NEAREST_MIPMAP_NEAREST ||
		interpolation == GL_LINEAR_MIPMAP_NEAREST ||
		interpolation == GL_NEAREST) {
		glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	} else {
		glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	CheckGLError::checkError("basetexture data 2");
	glTexImage2D(textureTarget, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
	CheckGLError::checkError("basetexture data 3");
	if (interpolation == GL_NEAREST_MIPMAP_NEAREST || interpolation == GL_NEAREST_MIPMAP_LINEAR ||
		interpolation == GL_LINEAR_MIPMAP_NEAREST || interpolation == GL_LINEAR_MIPMAP_LINEAR) {
		glGenerateMipmap(m_textureType);
	}
	CheckGLError::checkError("basetexture data 4");
	if (anisotropy > 0) {
		GLfloat maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(m_textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, std::min(anisotropy, maxAnisotropy));
	}
	CheckGLError::checkError("basetexture data 5");
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, wrapping);
	CheckGLError::checkError("basetexture data 6");
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_R, wrapping);
	CheckGLError::checkError("basetexture data end load");
}*/





