#pragma once

#include "Shader.hpp"

class ForwardAmbientLightShader : public Shader {
public:
	ForwardAmbientLightShader();

	void setAmbientLight(const glm::vec3& ambientLight);
};



