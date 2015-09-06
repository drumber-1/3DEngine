#pragma once

#include "Shader.hpp"
#include "../Material.hpp"
#include "../lighting/DirectionalLight.hpp"

class PhongShader : public Shader {
public:
	PhongShader();

	inline void setModelToProjectionMatrix(const glm::mat4& matrix) { setUniform("modelToProjectionMatrix", matrix); }
	inline void setModelToWorldMatrix(const glm::mat4& matrix) { setUniform("modelToWorldMatrix", matrix); }
	inline void setEyePositionWorld(const glm::vec3 eyePositionWorld) { setUniform("eyePositionWorld", eyePositionWorld); }
	inline void setModColour(const glm::vec4& colour) { setUniform("modColour", colour); }
	inline void setReflectivity(float reflectivity) { setUniform("reflectivity", reflectivity); }
	inline void setSpecularIndex(float specularIndex) { setUniform("specularIndex", specularIndex); }
	inline void setAmbientLight(const glm::vec3& ambientLight) { setUniform("ambientLight", ambientLight); }

	void setMaterial(const Material& material);
	void setDirectiobalLight(const DirectionalLight& directionalLight);
};
