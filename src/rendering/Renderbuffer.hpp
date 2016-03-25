#pragma once

#include <GL/glew.h>

class Renderbuffer {
public:
	Renderbuffer(GLenum bufferType, int width, int height)  : m_bufferType(bufferType),
															   m_width(width),
															   m_height(height) {
		glGenRenderbuffers(1, &m_bufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_bufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, bufferType, m_width, m_height);
	}

	~Renderbuffer() { glDeleteRenderbuffers(1, &m_bufferID); }
	Renderbuffer(const Renderbuffer& other) = delete;
	Renderbuffer& operator=(const Renderbuffer& other) = delete;
	Renderbuffer(Renderbuffer&& other) : m_bufferType(other.m_bufferType),
	m_width(other.m_width),
	m_height(other.m_height) {
		m_bufferID = other.m_bufferID;
	};
	Renderbuffer& operator=(Renderbuffer&& other) = delete;

	void bind(GLenum textureUnit) const {
		glBindRenderbuffer(GL_RENDERBUFFER, m_bufferID);
	}
	GLuint getID() { return m_bufferID; }
protected:
	GLuint m_bufferID;
	const GLenum m_bufferType;
	const int m_width;
	const int m_height;
};




