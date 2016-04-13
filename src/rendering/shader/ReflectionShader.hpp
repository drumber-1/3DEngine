#pragma once

#include "Shader.hpp"

class ReflectionShader : public Shader {
public:
	ReflectionShader();

	virtual void setCamera(const BaseCameraComponent& camera) override;

	virtual void setMaterial(const Material& material) override;

	virtual void draw(const RenderComponent& renderComponent) override;
};
