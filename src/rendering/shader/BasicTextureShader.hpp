#pragma once

#include "Shader.hpp"
#include "../Material.hpp"

class BasicTextureShader : public Shader {
public:
	BasicTextureShader();

	void setModelToProjectionMatrix(glm::mat4 matrix);
	void setModColour(glm::vec4 colour);
	void setMaterial(const Material& material);
};



