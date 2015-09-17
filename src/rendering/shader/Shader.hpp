#pragma once

#include "../Camera.hpp"
#include "../Material.hpp"
#include "BaseShader.hpp"

class Shader : public BaseShader {
public:
	Shader(const std::string &vertexShader, const std::string& fragmentShader);

	virtual void setCamera(const Camera& camera);
	virtual void setMaterial(const Material& material) {};

	inline void setModelToWorldMatrix(const glm::mat4& matrix) { setUniform("modelToWorldMatrix", matrix); }
	inline void setWorldToProjectionMatrix(const glm::mat4& matrix) { setUniform("worldToProjectionMatrix", matrix); }
};



