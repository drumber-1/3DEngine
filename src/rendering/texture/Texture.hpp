#pragma once

#include <string>
#include <array>
#include <GL/glew.h>

#include "../../core/ResourceManager.hpp"

class Texture {
public:
	Texture(const std::string& filename, bool loadNow = true);

	void bind(GLint textureUnit) const;

	void load();
	inline void unload() { glDeleteTextures(1, &m_textureID); }

	static ResourceManager<Texture> textureManager;
private:
	std::string m_filename;
	GLenum m_textureType;
	GLuint m_textureID;
};



