#pragma once

#include <bits/stringfwd.h>
#include "Shader.hpp"

class LightShader : public Shader {
public:
	LightShader(const std::string &vertexShader, const std::string& fragmentShader);

	inline void setEyePositionWorld(const glm::vec3 eyePositionWorld) { setUniform("eyePositionWorld", eyePositionWorld); }

	inline void setReflectivity(float reflectivity) { setUniform("reflectivity", reflectivity); }
	inline void setSpecularIndex(float specularIndex) { setUniform("specularIndex", specularIndex); }

	virtual void setCamera(const CameraComponent& camera);
	virtual void setMaterial(const Material& material);
};



