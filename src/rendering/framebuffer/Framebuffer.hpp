#pragma once

#include <GL/glew.h>
#include <bits/unique_ptr.h>
#include "../texture/BaseTextureData.hpp"
#include "../Renderbuffer.hpp"

class Framebuffer {
public:
	Framebuffer(int width, int height);

	~Framebuffer() { glDeleteFramebuffers(1, &m_framebufferID); }
	Framebuffer(const Framebuffer& other) = delete;
	Framebuffer& operator=(const Framebuffer& other) = delete;
	Framebuffer(Framebuffer&& other) : m_width(other.m_width), m_height(other.m_height) {
		m_framebufferID = other.m_framebufferID;
		std::swap(m_colourData, other.m_colourData);
		std::swap(m_depthData, other.m_depthData);
	};
	Framebuffer& operator=(Framebuffer&& other) = delete;

	void bind();
	static void unbindAll();
private:
	GLuint m_framebufferID;
	const int m_width;
	const int m_height;
	std::unique_ptr<BaseTextureData> m_colourData;
	std::unique_ptr<Renderbuffer> m_depthData;
};



