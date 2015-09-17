#include "Shader.hpp"

Shader::Shader(const std::string &vertexShader, const std::string& fragmentShader) : BaseShader(vertexShader, fragmentShader) {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
}

void Shader::setCamera(const Camera &camera) {
	setWorldToProjectionMatrix(camera.getWorldToProjectionMatrix());
}
