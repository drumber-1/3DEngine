#pragma once

#include <bits/stringfwd.h>
#include "Shader.hpp"

class LightShader : public Shader {
public:
	LightShader(const std::string &vertexShader, const std::string& fragmentShader);

	virtual void setCamera(const CameraComponent& camera);
	virtual void setMaterial(const Material& material);
	virtual void draw(const RenderComponent& component);
};



