#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

class Model {
public:
	Model() { }

	Model(const std::vector<unsigned int>& indices,
		  const std::vector<glm::vec3>& positions,
		  const std::vector<glm::vec2>& texCoords,
		  const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(),
		  const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>()) :
			m_indices(indices),
			m_positions(positions),
			m_texCoords(texCoords),
			m_normals(normals),
			m_tangents(tangents) { }

	bool isValid() const;

	void calcNormals();

	void calcTangents();

	void finalize();

	void clearAll();

	inline void addVertex(const glm::vec3& vert) { m_positions.push_back(vert); }

	inline void addVertex(float x, float y, float z) { addVertex(glm::vec3(x, y, z)); }

	inline void addTexCoord(const glm::vec2& texCoord) { m_texCoords.push_back(texCoord); }

	inline void addTexCoord(float x, float y) { addTexCoord(glm::vec2(x, y)); }

	inline void addNormal(const glm::vec3& normal) { m_normals.push_back(normal); }

	inline void addNormal(float x, float y, float z) { addNormal(glm::vec3(x, y, z)); }

	inline void addTangent(const glm::vec3& tangent) { m_tangents.push_back(tangent); }

	inline void addTangent(float x, float y, float z) { addTangent(glm::vec3(x, y, z)); }

	void addTri(unsigned int index0, unsigned int index1, unsigned int index2);

	inline const std::vector<unsigned int>& getIndices() const { return m_indices; }

	inline const std::vector<glm::vec3>& getPositions() const { return m_positions; }

	inline const std::vector<glm::vec2>& getTexCoords() const { return m_texCoords; }

	inline const std::vector<glm::vec3>& getNormals() const { return m_normals; }

	inline const std::vector<glm::vec3>& getTangents() const { return m_tangents; }

	void makePlane(unsigned int nx, unsigned int ny, float scale);

private:
	std::vector<unsigned int> m_indices;
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec2> m_texCoords;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
};



