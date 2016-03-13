#include "LightShader.hpp"

LightShader::LightShader(const std::string &vertexShader, const std::string &fragmentShader) : Shader(vertexShader, fragmentShader) {
	addUniform("eyePositionWorld");
	addUniform("reflectivity");
	addUniform("specularIndex");

	setTextureUnit("theNormal");
	setTextureUnit("theSpec");
}

void LightShader::setCamera(const CameraComponent &camera) {
	Shader::setCamera(camera);
	setEyePositionWorld(camera.getPosition());
}

void LightShader::setMaterial(const Material &material) {
	Shader::setMaterial(material);
	setNormalMap(material.getNormal());
	setSpecMap(material.getSpec());
	setReflectivity(material.getReflectivity());
	setSpecularIndex(material.getSpecularIndex());
}
