#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace renderingUtil {
	GLuint createArrayBufferObject(const std::vector<glm::vec2>& data, unsigned int attrib);

	GLuint createArrayBufferObject(const std::vector<glm::vec3>& data, unsigned int attrib);

	GLuint createIndexArrayBufferObject(const std::vector<unsigned int>& data);
}