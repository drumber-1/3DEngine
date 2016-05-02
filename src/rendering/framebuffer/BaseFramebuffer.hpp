#pragma once

#include <iostream>
#include <GL/glew.h>
#include "../texture/BaseTextureData.hpp"
#include "../Renderbuffer.hpp"
#include "../CheckGLError.hpp"

class BaseFramebuffer {
public:
	BaseFramebuffer(int width, int height) : m_width(width), m_height(height) {
		glGenFramebuffers(1, &m_framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
	}

	~BaseFramebuffer() {
		if (m_framebufferID != 0) {
			glDeleteFramebuffers(1, &m_framebufferID);
		}
	}

	BaseFramebuffer(const BaseFramebuffer& other) = delete;

	BaseFramebuffer& operator=(const BaseFramebuffer& other) = delete;

	BaseFramebuffer(BaseFramebuffer&& other) : m_width(other.m_width), m_height(other.m_height) {
		m_framebufferID = other.m_framebufferID;
		other.m_framebufferID = 0;
	};

	BaseFramebuffer& operator=(BaseFramebuffer&& other) = delete;

	void bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		glViewport(0, 0, m_width, m_height);
	}

	inline bool isComplete() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	};

	void printStatus() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		GLenum ans = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch (ans) {
			case GL_FRAMEBUFFER_COMPLETE:
				std::cout << "Framebuffer complete\n";
				break;
			case GL_FRAMEBUFFER_UNDEFINED:
				std::cout << "Framebuffer undefined\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				std::cout << "Framebuffer incomplete attachment\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				std::cout << "Framebuffer missing attachment\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				std::cout << "Framebuffer incomplete draw buffer\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				std::cout << "Framebuffer incomplete read buffer\n";
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				std::cout << "Framebuffer unsupported\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				std::cout << "Framebuffer incomplete multisample\n";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				std::cout << "Framebuffer incomplete layer targets\n";
				break;
			default:
				std::cout << "Unknown status";
				break;
		}
	}

	static void unbindAll() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

private:
	GLuint m_framebufferID;
	const int m_width;
	const int m_height;
};
