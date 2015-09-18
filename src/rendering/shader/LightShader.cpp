#include "LightShader.hpp"

LightShader::LightShader(const std::string &vertexShader, const std::string &fragmentShader) : Shader(vertexShader, fragmentShader) {
	addUniform("eyePositionWorld");
	addUniform("reflectivity");
	addUniform("specularIndex");
}

void LightShader::setCamera(const Camera &camera) {
	Shader::setCamera(camera);
	setEyePositionWorld(camera.getPosition());
}

void LightShader::setMaterial(const Material &material) {
	Shader::setMaterial(material);
	setReflectivity(material.getReflectivity());
	setSpecularIndex(material.getSpecularIndex());
}
