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

		glm::vec3 side1 = m_positions[i1] - m_positions[i0];
		glm::vec3 side2 = m_positions[i2] - m_positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(side2, side1));

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

void Model::finalize() {
	if (isValid()) {
		return;
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

	return;
}

void Model::clearAll() {
	m_positions.clear();
	m_indices.clear();
	m_texCoords.clear();
	m_normals.clear();
	m_tangents.clear();
}

void Model::addTri(unsigned int index0, unsigned int index1, unsigned int index2) {
	m_indices.push_back(index0);
	m_indices.push_back(index1);
	m_indices.push_back(index2);
}

void Model::makePlane(unsigned int nx, unsigned int ny, float scale) {
	clearAll();

	float xCellOffset = nx / 2.0f;
	float yCellOffset = ny / 2.0f;

	m_positions.resize(4 * nx * ny);
	m_texCoords.resize(4 * nx * ny);
	m_normals.resize(4 * nx * ny);
	for (unsigned int i = 0; i < nx; ++i) {
		for (unsigned int j = 0; j < ny; ++j) {
			int cellIndex = 4 * (i * ny + j);
			m_positions[cellIndex + 0].x = (i - xCellOffset) * scale;
			m_positions[cellIndex + 0].y = 0.0f;
			m_positions[cellIndex + 0].z = (j - yCellOffset) * scale;
			m_texCoords[cellIndex + 0].x = 0.0f;
			m_texCoords[cellIndex + 0].y = 0.0f;
			m_normals[cellIndex + 0].x = 0.0f;
			m_normals[cellIndex + 0].y = 1.0f;
			m_normals[cellIndex + 0].z = 0.0f;

			m_positions[cellIndex + 1].x = (i - xCellOffset) * scale;
			m_positions[cellIndex + 1].y = 0.0f;
			m_positions[cellIndex + 1].z = (j - yCellOffset + 1) * scale;
			m_texCoords[cellIndex + 1].x = 0.0f;
			m_texCoords[cellIndex + 1].y = 1.0f;
			m_normals[cellIndex + 1].x = 0.0f;
			m_normals[cellIndex + 1].y = 1.0f;
			m_normals[cellIndex + 1].z = 0.0f;

			m_positions[cellIndex + 2].x = (i - xCellOffset + 1) * scale;
			m_positions[cellIndex + 2].y = 0.0f;
			m_positions[cellIndex + 2].z = (j - yCellOffset + 1) * scale;
			m_texCoords[cellIndex + 2].x = 1.0f;
			m_texCoords[cellIndex + 2].y = 1.0f;
			m_normals[cellIndex + 2].x = 0.0f;
			m_normals[cellIndex + 2].y = 1.0f;
			m_normals[cellIndex + 2].z = 0.0f;

			m_positions[cellIndex + 3].x = (i - xCellOffset + 1) * scale;
			m_positions[cellIndex + 3].y = 0.0f;
			m_positions[cellIndex + 3].z = (j - yCellOffset) * scale;
			m_texCoords[cellIndex + 3].x = 1.0f;
			m_texCoords[cellIndex + 3].y = 0.0f;
			m_normals[cellIndex + 3].x = 0.0f;
			m_normals[cellIndex + 3].y = 1.0f;
			m_normals[cellIndex + 3].z = 0.0f;
		}
	}

	m_indices.resize(6 * nx * ny);
	unsigned int count = 0;
	for (unsigned int i = 0; i < nx; ++i) {
		for (unsigned int j = 0; j < ny; ++j) {
			unsigned int cellIndex = 4 * (i * ny + j);
			m_indices[count++] = cellIndex;
			m_indices[count++] = cellIndex + 1;
			m_indices[count++] = cellIndex + 2;

			m_indices[count++] = cellIndex;
			m_indices[count++] = cellIndex + 2;
			m_indices[count++] = cellIndex + 3;
		}
	}

}
