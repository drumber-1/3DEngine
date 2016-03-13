#pragma once

#include "BaseShader.hpp"

#include "../Material.hpp"
#include "../../components/CameraComponent.hpp"

class Shader : public BaseShader {
public:
	Shader(const std::string &vertexShader, const std::string& fragmentShader);

	inline void setModColour(const glm::vec4& colour) { setUniform("modColour", colour); }
	inline void setModelToWorldMatrix(const glm::mat4& matrix) { setUniform("modelToWorldMatrix", matrix); }
	inline void setWorldToProjectionMatrix(const glm::mat4& matrix) { setUniform("worldToProjectionMatrix", matrix); }

	virtual void setCamera(const CameraComponent& camera);
	virtual void setMaterial(const Material& material);
};



