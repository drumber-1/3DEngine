#pragma once

#include "BaseShader.hpp"

#include "../Material.hpp"
#include "../../components/camera/BaseCameraComponent.hpp"
#include "../../components/RenderComponent.hpp"

class Shader : public BaseShader {
public:
	Shader(const std::string& vertexShader,
		   const std::string& fragmentShader) : BaseShader(vertexShader, fragmentShader) { };

	Shader(const std::string& vertexShader,
		   const std::string& fragmentShader,
		   const std::string& geometryShader) : BaseShader(vertexShader, fragmentShader, geometryShader) { };

	virtual void setCamera(const BaseCameraComponent& camera) = 0;

	virtual void setMaterial(const Material& material) = 0;

	virtual void draw(const RenderComponent& renderComponent) = 0;
};



