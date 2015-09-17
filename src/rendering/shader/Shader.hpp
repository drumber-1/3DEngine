#pragma once

#include "../Camera.hpp"
#include "../Material.hpp"
#include "BaseShader.hpp"

class Shader : public BaseShader {
public:
	Shader(const std::string &vertexShader, const std::string& fragmentShader);

	virtual void setCamera(const Camera& camera) = 0;
	virtual void setMaterial(const Material& material) = 0;

	inline void setModelToWorldMatrix(const glm::mat4& matrix) { setUniform("modelToWorldMatrix", matrix); }
};



