#pragma once

#include "BaseShader.hpp"
#include "../../components/CameraComponent.hpp"

class SkyboxShader : public BaseShader {
public:
	SkyboxShader();
	void setCamera(const CameraComponent& camera);
	void setAmbientLight(const glm::vec3& ambientLight);
	void setModColour(const glm::vec4& colour);
};




