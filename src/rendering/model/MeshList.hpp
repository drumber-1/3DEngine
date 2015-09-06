#pragma once

#include <string>
#include <unordered_map>

#include "Mesh.hpp"
#include "Model.hpp"

class MeshList {
public:
	inline void add(const std::string& fileName) { m_meshes.emplace(std::make_pair(fileName, Mesh(fileName))); }
	inline void add(const std::string& name, const Model& model) { m_meshes.emplace(std::make_pair(name, Mesh(model))); }

	inline void draw(const std::string& identifier) const { getMesh(identifier).draw(); }

	inline void load(const std::string& identifier) { getMesh(identifier).load(); }
	inline void unload(const std::string& identifier) { getMesh(identifier).unload(); }
	inline bool isLoaded(const std::string& identifier) const { return getMesh(identifier).isLoaded(); }

	inline const Mesh& getMesh(const std::string& identifier) const { return  m_meshes.find(identifier)->second; }
	inline Mesh& getMesh(const std::string& identifier) { return m_meshes.find(identifier)->second; }
private:
	std::unordered_map<std::string, Mesh> m_meshes;
};



