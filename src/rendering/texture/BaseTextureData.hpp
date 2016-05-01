#pragma once

#include <GL/glew.h>

class BaseTextureData {
public:
	BaseTextureData(GLenum textureType, int width, int height);

	~BaseTextureData() { glDeleteTextures(1, &m_textureID); }

	BaseTextureData(const BaseTextureData& other) = delete;

	BaseTextureData& operator=(const BaseTextureData& other) = delete;

	BaseTextureData(BaseTextureData&& other) : m_textureType(other.m_textureType),
											   m_width(other.m_width),
											   m_height(other.m_height) {
		m_textureID = other.m_textureID;
	};

	BaseTextureData& operator=(BaseTextureData&& other) = delete;

	void bind(GLenum textureUnit) const;

	void setParameters(GLint interpolation, GLint wrapping, float anisotropy);

	void load(const GLvoid* data, GLenum textureTarget, GLenum format);

	void generateMipmaps();

	//void load(const GLvoid* data, GLenum textureTarget);

	void setAsShadowMap(GLenum textureTarget, float borderIntensity);

	//void load(const GLvoid* data, GLenum textureTarget, GLenum format, GLint interpolation, GLint wrapping,
	//		  float anisotropy);

	GLuint getID() const { return m_textureID; }

protected:
	GLuint m_textureID;
	const GLenum m_textureType;
	const int m_width;
	const int m_height;
};



