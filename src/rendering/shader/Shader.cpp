#include "Shader.hpp"

Shader::Shader(const std::string &vertexShader, const std::string& fragmentShader) : BaseShader(vertexShader, fragmentShader) {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("modColour");
	setTextureUnit("theTexture");
}

void Shader::setCamera(const CameraComponent& camera) {
	setWorldToProjectionMatrix(camera.getWorldToProjectionMatrix());
}

void Shader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	setTexture(material.getTexture());
}
