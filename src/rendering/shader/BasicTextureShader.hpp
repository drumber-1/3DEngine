#pragma once

#include "Shader.hpp"

class BasicTextureShader : public Shader {
public:
	BasicTextureShader();

	void setModelToProjectionMatrix(glm::mat4 matrix);
	void setModColour(glm::vec4 colour);
};



