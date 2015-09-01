#include "Model.hpp"

bool Model::isValid() const {
	return m_positions.size() == m_texCoords.size() &&
		   m_texCoords.size() == m_normals.size() &&
		   m_normals.size() == m_tangents.size();
}

void Model::calcNormals() {
	m_normals.clear();
	m_normals.resize(m_positions.size());

	for (unsigned int i = 0; i < m_indices.size(); i += 3) {
		unsigned int i0 = m_indices[i];
		unsigned int i1 = m_indices[i + 1];
		unsigned int i2 = m_indices[i + 2];

		glm::vec3 v1 = m_positions[i1] - m_positions[i0];
		glm::vec3 v2 = m_positions[i2] - m_positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v2, v1));

		m_normals[i0] += normal;
		m_normals[i1] += normal;
		m_normals[i2] += normal;
	}

	for (unsigned int i = 0; i < m_normals.size(); ++i) {
		m_normals[i] = glm::normalize(m_normals[i]);
	}
}

void Model::calcTangents() {
	m_tangents.clear();
	m_tangents.resize(m_positions.size());

	for (unsigned int i = 0; i < m_indices.size(); i += 3) {
		unsigned int i0 = m_indices[i];
		unsigned int i1 = m_indices[i + 1];
		unsigned int i2 = m_indices[i + 2];

		glm::vec3 physicalSide1 = m_positions[i1] - m_positions[i0];
		glm::vec3 physicalSide2 = m_positions[i2] - m_positions[i0];

		glm::vec2 textureSide1 = m_texCoords[i1] - m_texCoords[i0];
		glm::vec2 textureSide2 = m_texCoords[i2] - m_texCoords[i0];

		glm::mat2 texMat(textureSide1, textureSide2);

		float det = glm::determinant(texMat);
		float f = 0.0f;
		if (det != 0.0f) {
			f = 1.0f / det;
		}

		glm::vec3 tangent;

		tangent.x = f * (textureSide2.y * physicalSide1.x - textureSide1.y * physicalSide2.x);
		tangent.y = f * (textureSide2.y * physicalSide1.y - textureSide1.y * physicalSide2.y);
		tangent.z = f * (textureSide2.y * physicalSide1.z - textureSide1.y * physicalSide2.z);

		m_tangents[i0] += tangent;
		m_tangents[i1] += tangent;
		m_tangents[i2] += tangent;

	}

	for (unsigned int i = 0; i < m_tangents.size(); ++i) {
		m_tangents[i] = glm::normalize(m_tangents[i]);
	}

}

Model Model::finalize() {
	if (isValid()) {
		return *this;
	}

	if (m_texCoords.size() == 0) {
		m_texCoords.resize(m_positions.size());
	}

	if (m_normals.size() == 0) {
		calcNormals();
	}

	if (m_tangents.size() == 0) {
		calcTangents();
	}

	assert(isValid());

	return *this;
}

void Model::addTri(unsigned int index0, unsigned int index1, unsigned int index2) {
	m_indices.push_back(index0);
	m_indices.push_back(index1);
	m_indices.push_back(index2);
}
