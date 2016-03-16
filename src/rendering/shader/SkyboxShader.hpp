#pragma once

#include "Shader.hpp"
#include "../../components/CameraComponent.hpp"

class SkyboxShader : public Shader {
public:
	SkyboxShader();

	void setAmbientLight(const glm::vec3& ambientLight);
	virtual void setCamera(const CameraComponent& camera);
	virtual void setMaterial(const Material& material);
	virtual void draw(const RenderComponent& renderComponent);
};




