#include "Shader.hpp"

#include <iostream>

void Shader::addUniform(const std::string &uniformName) {
	GLint uniformLocation = glGetUniformLocation(m_shaderData.getProgramID(), uniformName.c_str());
	//assert(uniformLocation != -1);
	if (uniformLocation == -1) {
		std::cerr << "Couldn't find uniform " << uniformName << "\n";
	}

	m_uniformLocations.insert(std::pair<std::string, GLint>(uniformName, uniformLocation));
}
