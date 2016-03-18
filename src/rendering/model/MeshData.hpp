#pragma once

#include <array>
#include <GL/glew.h>

#include "Model.hpp"

class MeshData {
public:
	MeshData(const Model& model);

	~MeshData() {
		glDeleteVertexArrays(1, &m_vertexArrayObjectID);
		glDeleteBuffers(NUM_BUFFERS, m_BufferObjectIDs._M_elems);
	}
	MeshData(const MeshData& other) = delete;
	MeshData& operator=(const MeshData& other) = delete;
	MeshData(MeshData&& other) {
		m_vertexArrayObjectID = other.m_vertexArrayObjectID;
		m_BufferObjectIDs = other.m_BufferObjectIDs;

	};
	MeshData& operator=(MeshData&& other) = delete;

	void draw() const;
private:
	enum BufferType {
		POSITION,
		TEXCOORD,
		NORMAL,
		TANGENT,
		INDEX,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObjectID;
	std::array<GLuint, NUM_BUFFERS> m_BufferObjectIDs;
	unsigned int m_nIndices;
};



