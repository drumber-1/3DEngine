#include "BasicTextureShader.hpp"
#include "../texture/Texture.hpp"

BasicTextureShader::BasicTextureShader() : Shader("basicTexture_vert.glsl", "basicTexture_frag.glsl") {
	addUniform("worldToProjectionMatrix");
	addUniform("modelToWorldMatrix");
	addUniform("modColour");
}

void BasicTextureShader::setMaterial(const Material &material) {
	setModColour(material.getModColour());
	material.getTexture()->bind();
}
