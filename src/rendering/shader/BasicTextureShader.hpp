#pragma once

#include "BaseShader.hpp"
#include "../Material.hpp"

class BasicTextureShader : public BaseShader {
public:
	BasicTextureShader();

	inline void setWorldToProjectionMatrix(const glm::mat4& matrix) { setUniform("worldToProjectionMatrix", matrix); }
	inline void setModelToWorldMatrix(const glm::mat4& matrix) { setUniform("modelToWorldMatrix", matrix); }
	inline void setModColour(const glm::vec4& colour) { setUniform("modColour", colour); }
	void setMaterial(const Material& material);
};



