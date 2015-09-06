#pragma once

#include "Shader.hpp"
#include "../Material.hpp"
#include "../lighting/DirectionalLight.hpp"

class PhongShader : public Shader {
public:
	PhongShader();

	void setModelToProjectionMatrix(glm::mat4 matrix);
	void setModelToWorldMatrix(glm::mat4 matrix);
	void setModColour(glm::vec4 colour);
	void setMaterial(const Material& material);
	void setAmbientLight(glm::vec3 ambientLight);
	void setDirectiobalLight(const DirectionalLight& directionalLight);
};
