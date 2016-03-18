#pragma once

#include <GL/glew.h>

class TextureData {
public:
	TextureData(GLenum textureType, int width, int height, const GLvoid* data);

	~TextureData() { glDeleteTextures(1, &m_textureID); }
	TextureData(const TextureData& other) = delete;
	TextureData& operator=(const TextureData& other) = delete;
	TextureData(TextureData&& other) : m_textureType(other.m_textureType),
									   m_width(other.m_width),
									   m_height(other.m_height) {
		m_textureID = other.m_textureID;
	};
	TextureData& operator=(TextureData&& other) = delete;

	void bind(GLenum textureUnit) const;
	void load(int width, int height, const GLvoid* data, GLenum textureType, GLenum textureTarget);

private:
	GLuint m_textureID;
	const GLenum m_textureType;
	const int m_width;
	const int m_height;
};



