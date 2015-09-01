#pragma once

#include <array>
#include <GL/glew.h>

#include "Model.hpp"

class MeshData {
public:
	MeshData(const Model& model);
	virtual ~MeshData();

	void draw() const;
private:
	MeshData(MeshData& other) {}
	void operator=(MeshData& other) {}

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



