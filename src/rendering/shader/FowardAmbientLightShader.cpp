#include "ForwardAmbientLightShader.hpp"

ForwardAmbientLightShader::ForwardAmbientLightShader() : Shader("forward_ambient_vert.glsl", "forward_ambient_frag.glsl") {
	addUniform("ambientLight");
}

void ForwardAmbientLightShader::setAmbientLight(const glm::vec3& ambientLight) {
	setUniform("ambientLight", ambientLight);
}