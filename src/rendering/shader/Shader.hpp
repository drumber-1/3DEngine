#pragma once

#include <string>
#include <glm/glm.hpp>

#include "ShaderData.hpp"

class Shader {
public:
	Shader(const std::string &vertexShader, const std::string& fragmentShader) : m_shaderData(vertexShader, fragmentShader) {}

	void useShader() const;

	void addUniform(const std::string& uniformName);

	void setUniform(const std::string& uniformName, int uniformValue) const;
	void setUniform(const std::string& uniformName, float uniformValue) const;
	void setUniform(const std::string& uniformName, const glm::vec3& uniformValue) const;
	void setUniform(const std::string &uniformName, const glm::vec4& uniformValue) const;
	void setUniform(const std::string& uniformName, const glm::mat4& uniformValue) const;
private:
	ShaderData m_shaderData;
	std::map<std::string, GLint> m_uniformLocations;
};



