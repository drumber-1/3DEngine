#include "MeshData.hpp"

#include "../renderingUtil.hpp"

MeshData::MeshData(const Model &model) : m_nIndices((unsigned int)model.getIndices().size()) {
	assert(model.isValid());

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	m_BufferObjectIDs[BufferType::POSITION] = renderingUtil::createArrayBufferObject(model.getPositions(), 0);
	m_BufferObjectIDs[BufferType::TEXCOORD] = renderingUtil::createArrayBufferObject(model.getTexCoords(), 1);
	m_BufferObjectIDs[BufferType::NORMAL] = renderingUtil::createArrayBufferObject(model.getNormals(), 2);
	m_BufferObjectIDs[BufferType::TANGENT] = renderingUtil::createArrayBufferObject(model.getTangents(), 3);
	m_BufferObjectIDs[BufferType::INDEX] = renderingUtil::createIndexArrayBufferObject(model.getIndices());
}

MeshData::~MeshData() {
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);
	glDeleteBuffers(NUM_BUFFERS, m_BufferObjectIDs._M_elems);
}

void MeshData::draw() const {
	glBindVertexArray(m_vertexArrayObjectID);
	glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
}
