#pragma once

#include <string>
#include <glm/glm.hpp>

#include "ShaderData.hpp"
#include "../texture/Texture.hpp"

class BaseShader {
public:
	BaseShader(const std::string &vertexShader, const std::string& fragmentShader) : m_shaderData("res/shaders/" + vertexShader, "res/shaders/" + fragmentShader) {}

	inline void useShader() const { m_shaderData.useProgram(); }

	inline void setUniform(const std::string& uniformName, int uniformValue) const { glUniform1i(m_uniformLocations.at(uniformName), uniformValue); }
	inline void setUniform(const std::string& uniformName, float uniformValue) const { glUniform1f(m_uniformLocations.at(uniformName), uniformValue); }
	inline void setUniform(const std::string& uniformName, const glm::vec3& uniformValue) const { glUniform3fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]); }
	inline void setUniform(const std::string& uniformName, const glm::vec4& uniformValue) const { glUniform4fv(m_uniformLocations.at(uniformName), 1, &uniformValue[0]); }
	inline void setUniform(const std::string& uniformName, const glm::mat4& uniformValue) const { glUniformMatrix4fv(m_uniformLocations.at(uniformName), 1, GL_FALSE, &uniformValue[0][0]); }
	inline void setUniform(const std::string& uniformName, const Texture* texture) const {
		glUniform1i(m_uniformLocations.at(uniformName), m_textureUnits.at(uniformName));
		texture->bind(GL_TEXTURE0 + m_textureUnits.at(uniformName));
	}

protected:
	ShaderData m_shaderData;

	void addUniform(const std::string& uniformName);
	void setTextureUnit(const std::string& uniformName);
private:
	std::map<std::string, GLint> m_uniformLocations;
	std::map<std::string, GLint> m_textureUnits;
};



