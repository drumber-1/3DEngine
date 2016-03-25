#pragma once

#include "Shader.hpp"

class ShadowDepthShader : public Shader {
public:
	ShadowDepthShader();

	virtual void setCamera(const BaseCameraComponent& camera);
	virtual void setMaterial(const Material& material) {};
	virtual void draw(const RenderComponent& renderComponent);
};



