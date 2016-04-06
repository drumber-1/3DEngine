#pragma once

#include "Shader.hpp"

class ShadowDepthCubeShader : public Shader {
public:
	ShadowDepthCubeShader();

	virtual void setCamera(const BaseCameraComponent& camera);

	virtual void setMaterial(const Material& material) { };

	virtual void draw(const RenderComponent& renderComponent);
};