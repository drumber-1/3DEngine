#include "BasicTextureShader.hpp"

BasicTextureShader::BasicTextureShader() : Shader("res/shaders/basicTexture_vert.glsl", "res/shaders/basicTexture_frag.glsl") {
	addUniform("modelToProjectionMatrix");
	addUniform("modColour");
}

void BasicTextureShader::setModelToProjectionMatrix(glm::mat4 matrix) {
	setUniform("modelToProjectionMatrix", matrix);
}

void BasicTextureShader::setModColour(glm::vec4 colour) {
	setUniform("modColour", colour);
}
