#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>
#include <map>

class ShaderData {
public:
	ShaderData(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	ShaderData(const std::string& vertexShader, const std::string& fragmentShader);

	virtual ~ShaderData();

	inline void useProgram() const { glUseProgram(m_programID); }

	inline GLuint getProgramID() const { return m_programID; }

private:
	std::string readShaderCode(const std::string& fileName);

	GLuint addShaderToProgram(const std::string& text, GLenum type);

	void linkProgram();

	GLuint m_programID;
};



