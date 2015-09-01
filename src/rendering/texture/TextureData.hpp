#pragma once

#include <GL/glew.h>

class TextureData {
public:
	TextureData(int width, int height, const GLvoid* data);
	void bind() const;
private:
	GLuint m_textureID;
	int m_width;
	int m_height;
};



