#include "BaseShader.hpp"

#include <iostream>

void BaseShader::addUniform(const std::string &uniformName) {
	GLint uniformLocation = glGetUniformLocation(m_shaderData.getProgramID(), uniformName.c_str());
	if (uniformLocation == -1) {
		std::cerr << "Couldn't find uniform " << uniformName << "\n";
	}

	m_uniformLocations.insert(std::pair<std::string, GLint>(uniformName, uniformLocation));
}

void BaseShader::setTextureUnit(const std::string& uniformName) {
	GLint uniformLocation = glGetUniformLocation(m_shaderData.getProgramID(), uniformName.c_str());
	if (uniformLocation == -1) {
		std::cerr << "Couldn't find uniform " << uniformName << "\n";
	}
	m_uniformLocations.insert(std::pair<std::string, GLint>(uniformName, uniformLocation));
	size_t textureUnit = m_textureUnits.size();
	m_textureUnits.insert(std::pair<std::string, size_t>(uniformName, textureUnit));
}
