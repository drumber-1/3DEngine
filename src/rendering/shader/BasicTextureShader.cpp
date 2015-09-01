#include "BasicTextureShader.hpp"

BasicTextureShader::BasicTextureShader() : Shader("res/shaders/test_vert.glsl", "res/shaders/test_frag.glsl") {
	addUniform("modelToProjectionMatrix");
	addUniform("modColour");
}

void BasicTextureShader::setModelToProjectionMatrix(glm::mat4 matrix) {
	setUniform("modelToProjectionMatrix", matrix);
}

void BasicTextureShader::setModColour(glm::vec4 colour) {
	setUniform("modColour", colour);
}
