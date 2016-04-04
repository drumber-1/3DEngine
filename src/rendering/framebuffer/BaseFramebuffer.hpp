#pragma once

#include <GL/glew.h>
#include <bits/unique_ptr.h>
#include "../texture/BaseTextureData.hpp"
#include "../Renderbuffer.hpp"

class BaseFramebuffer {
public:
	BaseFramebuffer(int width, int height) : m_width(width), m_height(height) {
		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	}

	~BaseFramebuffer() { glDeleteFramebuffers(1, &m_framebufferID); }

	BaseFramebuffer(const BaseFramebuffer& other) = delete;

	BaseFramebuffer& operator=(const BaseFramebuffer& other) = delete;

	BaseFramebuffer(BaseFramebuffer&& other) : m_width(other.m_width), m_height(other.m_height) {
		m_framebufferID = other.m_framebufferID;
	};

	BaseFramebuffer& operator=(BaseFramebuffer&& other) = delete;

	void bind() const {
		glViewport(0, 0, m_width, m_height);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	}

	inline bool isComplete() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	};

	static void unbindAll() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

private:
	GLuint m_framebufferID;
	const int m_width;
	const int m_height;
};
