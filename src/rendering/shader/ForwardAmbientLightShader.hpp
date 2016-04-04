#pragma once

#include "Shader.hpp"

class ForwardAmbientLightShader : public Shader {
public:
	ForwardAmbientLightShader();

	void setAmbientLight(const glm::vec3& ambientLight);

	virtual void setCamera(const BaseCameraComponent& camera);

	virtual void setMaterial(const Material& material);

	virtual void draw(const RenderComponent& renderComponent);
};



