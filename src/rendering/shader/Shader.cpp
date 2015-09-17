#include "Shader.hpp"

Shader::Shader(const std::string &vertexShader, const std::string& fragmentShader) : BaseShader(vertexShader, fragmentShader) {
	addUniform("modelToWorldMatrix");
}