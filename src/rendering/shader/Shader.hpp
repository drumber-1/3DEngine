#pragma once

#include <string>
#include <glm/glm.hpp>

#include "ShaderData.hpp"

class Shader {
public:
	Shader(const std::string &vertexShader, const std::string& fragmentShader) : m_shaderData("res/shaders/" + vertexShader, "res/shaders/" + fragmentShader) {}

	inline void useShader() const { m_shaderData.useProgram(); }

	void addUniform(const std::string& uniformName);

	inline void setUniform(const std::string& uniformName, int uniformValue) const { glUniform1i(m_uniformLocations.at(uniformName), uniformValue); }
	inline void setUniform(const std::string& uniformName, float uniformValue) const { glUniform1f(m_uniformLocations.at(uniformName), uniformValue); }
	inline void setUniform(const std::string& uniformName, const glm::vec3& uniformValue) const { glUniform3fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]); }
	inline void setUniform(const std::string &uniformName, const glm::vec4& uniformValue) const { glUniform4fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]); }
	inline void setUniform(const std::string& uniformName, const glm::mat4& uniformValue) const { glUniformMatrix4fv(m_uniformLocations.at(uniformName), 1, GL_FALSE, &uniformValue[0][0]); }
private:
	ShaderData m_shaderData;
	std::map<std::string, GLint> m_uniformLocations;
};



