#include "renderingUtil.hpp"

template<typename T>
GLuint createArrayBufferObjects(const std::vector<T>& data, unsigned int attrib, unsigned int floats_per_vert) {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, floats_per_vert, GL_FLOAT, GL_FALSE, 0, 0);

	return bufferID;
}

GLuint renderingUtil::createArrayBufferObject(const std::vector<glm::vec2>& data, unsigned int attrib) {
	return createArrayBufferObjects(data, attrib, 2);
}

GLuint renderingUtil::createArrayBufferObject(const std::vector<glm::vec3>& data, unsigned int attrib) {
	return createArrayBufferObjects(data, attrib, 3);
}

GLuint renderingUtil::createIndexArrayBufferObject(const std::vector<unsigned int>& data) {
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
	return bufferID;
}
