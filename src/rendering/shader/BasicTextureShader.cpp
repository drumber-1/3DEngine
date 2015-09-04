#include "BasicTextureShader.hpp"
#include "../texture/Texture.hpp"

BasicTextureShader::BasicTextureShader() : Shader("basicTexture_vert.glsl", "basicTexture_frag.glsl") {
	addUniform("modelToProjectionMatrix");
	addUniform("modColour");
}

void BasicTextureShader::setModelToProjectionMatrix(glm::mat4 matrix) {
	setUniform("modelToProjectionMatrix", matrix);
}

void BasicTextureShader::setModColour(glm::vec4 colour) {
	setUniform("modColour", colour);
}

void BasicTextureShader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	material.getTexture()->bind();
}
