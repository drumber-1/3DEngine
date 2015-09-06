#pragma once

#include "Shader.hpp"
#include "../Material.hpp"
#include "../lighting/DirectionalLight.hpp"

class PhongShader : public Shader {
public:
	PhongShader();

	inline void setModelToProjectionMatrix(glm::mat4 matrix) { setUniform("modelToProjectionMatrix", matrix); }
	inline void setModelToWorldMatrix(glm::mat4 matrix) { setUniform("modelToWorldMatrix", matrix); }
	inline void setModColour(glm::vec4 colour) { setUniform("modColour", colour); }
	inline void setAmbientLight(glm::vec3 ambientLight) { setUniform("ambientLight", ambientLight); }

	void setMaterial(const Material& material);
	void setDirectiobalLight(const DirectionalLight& directionalLight);
};
