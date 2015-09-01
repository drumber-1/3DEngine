#include "ShaderData.hpp"

#include <GL/glew.h>
#include <iostream>
#include <fstream>

ShaderData::ShaderData(const std::string &vertexShader, const std::string& fragmentShader) {
	m_programID = glCreateProgram();

	std::string vertexShaderCode = readShaderCode(vertexShader);
	std::string fragmentShaderCode = readShaderCode(fragmentShader);

	GLuint vertexShaderID = addShaderToProgram(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = addShaderToProgram(fragmentShaderCode, GL_FRAGMENT_SHADER);

	linkProgram();

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

ShaderData::~ShaderData() {
	glDeleteProgram(m_programID);
}

std::string ShaderData::readShaderCode(const std::string& fileName) {
	std::ifstream inFile(fileName);
	if (!inFile.good()) {
		std::cerr << "File, " << fileName << ", failed to load" << std::endl;
		exit(1);
	}
	return std::string(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());
}

GLuint ShaderData::addShaderToProgram(const std::string& shaderText, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);

	const GLchar* adapter[1];
	adapter[0] = shaderText.c_str();

	glShaderSource(shaderID, 1, adapter, 0);
	glCompileShader(shaderID);

	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, nullptr, buffer);
		std::cerr << "Shader compile error: " << buffer << "\n";
		delete buffer;
	}

	glAttachShader(m_programID, shaderID);
	return shaderID;
}

void ShaderData::linkProgram() {
	glLinkProgram(m_programID);

	GLint status;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, nullptr, buffer);
		std::cerr << "Shader link error: " << buffer << "\n";
		delete buffer;
	}
}
