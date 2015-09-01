#pragma once

#include <string>
#include <map>
#include <memory>

#include "Model.hpp"
#include "MeshData.hpp"

class Mesh {
public:
	Mesh(const std::string& fileName, bool loadNow = true);
	Mesh(const Model& model, bool loadNow = true);

	void load();
	void unload();
	bool isLoaded() const;

	void draw() const;
private:
	std::unique_ptr<MeshData> m_meshData;
	//TODO Avoid storing model for primitive shapes, using enums and hard-coded Model constructors probably
	//TODO Adhoc models will either have to be stored, or prevented from loading/unloading
	Model m_model;
	std::string m_fileName;
	const bool m_hasModel;
};



