#pragma once

#include <glm/glm.hpp>
#include <string>

#include "texture/Texture.hpp"

class Material {
public:
	Material(const Texture* texture,
			 glm::vec4 modColour = glm::vec4(1.0, 1.0, 1.0, 1.0),
			 float reflectivity = 1.0f,
			 float specularIndex = 32.0f,
			 const Texture* normalMap = Texture::textureManager.getPointer("default_normal.png"),
			 const Texture* dispMap = Texture::textureManager.getPointer("default_disp.png"),
	         float dispMapScale = 0.0f,
	         float dispMapBias = 0.0f) : m_texture(texture),
								         m_normalMap(normalMap),
	                                     m_dispMap(dispMap),
								         m_modColour(modColour),
	                                     m_reflectivity(reflectivity),
	                                     m_specularIndex(specularIndex),
	                                     m_dispMapScale(dispMapScale),
	                                     m_dispMapBias(dispMapBias) {}

	inline const Texture* getTexture() const { return m_texture; }
	inline const glm::vec4& getModColour() const { return m_modColour; }
	inline float getReflectivity() const { return m_reflectivity; }
	inline float getSpecularIndex() const { return m_specularIndex; }
private:
	const Texture* m_texture;
	const Texture* m_normalMap;
	const Texture* m_dispMap;

	glm::vec4 m_modColour;

	float m_reflectivity;
	float m_specularIndex;

	float m_dispMapScale;
	float m_dispMapBias;
};



