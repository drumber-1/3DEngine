#include "Mesh.hpp"

#include "MeshData.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Todo Check to see if this can be folded into MeshData

Mesh::Mesh(const std::string &fileName, bool loadNow) : m_fileName(fileName), m_hasModel(true) {
	if (loadNow) {
		load();
	}
}

Mesh::Mesh(const Model &model, bool loadNow) : m_model(model), m_hasModel(false) {
	if (loadNow) {
		load();
	}
}

void Mesh::load() {
	if (m_fileName == "") {
		m_meshData.reset(new MeshData(m_model));
	}

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(("res/models/" + m_fileName).c_str(),
											 aiProcess_Triangulate |
											 aiProcess_GenSmoothNormals |
											 aiProcess_FlipUVs |
											 aiProcess_CalcTangentSpace);

	assert(scene);

	const aiMesh* importedMesh = scene->mMeshes[0];

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<unsigned int> indices;

	const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
	for(unsigned int i = 0; i < importedMesh->mNumVertices; ++i) {
		const aiVector3D pos = importedMesh->mVertices[i];
		const aiVector3D normal = importedMesh->mNormals[i];
		const aiVector3D texCoord = importedMesh->HasTextureCoords(0) ? importedMesh->mTextureCoords[0][i] : aiZeroVector;
		const aiVector3D tangent = importedMesh->mTangents[i];

		positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
		normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
		tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
	}

	for(unsigned int i = 0; i < importedMesh->mNumFaces; ++i) {
		const aiFace& face = importedMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	m_meshData.reset(new MeshData(Model(indices, positions, texCoords, normals, tangents)));
}

void Mesh::unload() {
	m_meshData.reset();
}

bool Mesh::isLoaded() const {
	return m_meshData.get() == nullptr;
}

void Mesh::draw() const {
	m_meshData->draw();
}


