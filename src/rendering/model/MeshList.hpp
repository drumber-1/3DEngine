#pragma once

#include <string>
#include <unordered_map>

#include "Mesh.hpp"

class MeshList {
public:
	void add(const std::string& fileName) { m_meshes.emplace(std::make_pair(fileName, Mesh(fileName))); }

	void draw(const std::string& identifier) const { getMesh(identifier).draw(); }

	void load(const std::string& identifier) { getMesh(identifier).load(); }
	void unload(const std::string& identifier) { getMesh(identifier).unload(); }
	bool isLoaded(const std::string& identifier) const { return getMesh(identifier).isLoaded(); }

	const Mesh& getMesh(const std::string& identifier) const { return  m_meshes.find(identifier)->second; }
	Mesh& getMesh(const std::string& identifier) { return m_meshes.find(identifier)->second; }
private:
	std::unordered_map<std::string, Mesh> m_meshes;
};



