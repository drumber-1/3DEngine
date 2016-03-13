#pragma once

#include "BaseShader.hpp"
#include "../Material.hpp"
#include "../lighting/DirectionalLight.hpp"
#include "../lighting/PointLight.hpp"
#include "../lighting/SpotLight.hpp"
#include "Shader.hpp"

class PhongShader : public Shader {
public:
	PhongShader();

	inline void setEyePositionWorld(const glm::vec3 eyePositionWorld) { setUniform("eyePositionWorld", eyePositionWorld); }

	inline void setReflectivity(float reflectivity) { setUniform("reflectivity", reflectivity); }
	inline void setSpecularIndex(float specularIndex) { setUniform("specularIndex", specularIndex); }

	void setMaterial(const Material& material);
	void setCamera(const CameraComponent& camera);

	inline void setAmbientLight(const glm::vec3& ambientLight) { setUniform("ambientLight", ambientLight); }
	void setDirectionalLight(const DirectionalLight& directionalLight, int id);
	void setPointLight(const PointLight& pointLight, int id);
	void setSpotLight(const SpotLight& spotLight, int id);

private:
	static const int MAX_DIRECTIONAL_LIGHTS = 4;
	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;
};
