#include "Shader.hpp"

#include <cassert>
#include <iostream>

void Shader::useShader() const {
	m_shaderData.useProgram();
}

void Shader::addUniform(const std::string &uniformName) {
	GLint uniformLocation = glGetUniformLocation(m_shaderData.getProgramID(), uniformName.c_str());
	//assert(uniformLocation != -1);
	if (uniformLocation == -1) {
		std::cerr << "Couldn't find uniform " << uniformName << "\n";
	}

	m_uniformLocations.insert(std::pair<std::string, GLint>(uniformName, uniformLocation));
}

void Shader::setUniform(const std::string &uniformName, int uniformValue) const {
	glUniform1i(m_uniformLocations.at(uniformName), uniformValue);
}

void Shader::setUniform(const std::string &uniformName, float uniformValue) const {
	glUniform1f(m_uniformLocations.at(uniformName), uniformValue);
}

void Shader::setUniform(const std::string &uniformName, const glm::vec3& uniformValue) const {
	glUniform3fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]);
}

void Shader::setUniform(const std::string &uniformName, const glm::vec4& uniformValue) const {
	glUniform4fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]);
}

void Shader::setUniform(const std::string &uniformName, const glm::mat4& uniformValue) const {
	glUniformMatrix4fv(m_uniformLocations.at(uniformName), 1, GL_FALSE, &uniformValue[0][0]);
}
