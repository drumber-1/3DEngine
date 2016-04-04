#pragma once

#include "Shader.hpp"
#include "../../components/camera/BaseCameraComponent.hpp"

class SkyboxShader : public Shader {
public:
	SkyboxShader();

	void setAmbientLight(const glm::vec3& ambientLight);

	virtual void setCamera(const BaseCameraComponent& camera);

	virtual void setMaterial(const Material& material);

	virtual void draw(const RenderComponent& renderComponent);
};




