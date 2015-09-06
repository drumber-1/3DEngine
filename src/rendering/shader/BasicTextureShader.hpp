#pragma once

#include "Shader.hpp"
#include "../Material.hpp"

class BasicTextureShader : public Shader {
public:
	BasicTextureShader();

	inline void setModelToProjectionMatrix(const glm::mat4& matrix) { setUniform("modelToProjectionMatrix", matrix); }
	inline void setModColour(const glm::vec4& colour) { setUniform("modColour", colour); }
	void setMaterial(const Material& material);
};



