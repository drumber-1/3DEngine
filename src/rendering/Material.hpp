#pragma once

#include <glm/glm.hpp>
#include <string>

#include "texture/Texture.hpp"

class Material {
public:
	Material(const Texture* texture,
			 const Texture* normalMap = nullptr,
			 const Texture* specMap = nullptr,
			 glm::vec4 modColour = glm::vec4(1.0, 1.0, 1.0, 1.0),
			 float reflectivity = 1.0f,
			 float specularIndex = 32.0f,
			 bool reflections = false)
			: m_texture(texture),
			  m_normalMap(normalMap),
			  m_specMap(specMap),
			  m_modColour(modColour),
			  m_reflectivity(reflectivity),
			  m_specularIndex(specularIndex),
			  m_reflections(reflections) {
		setDefaultTextures();
	}

	inline const Texture* getTexture() const { return m_texture; }

	inline const Texture* getNormal() const { return m_normalMap; }

	inline const Texture* getSpec() const { return m_specMap; }

	inline const glm::vec4& getModColour() const { return m_modColour; }

	inline float getReflectivity() const { return m_reflectivity; }

	inline float getSpecularIndex() const { return m_specularIndex; }

	inline bool hasReflections() const { return m_reflections; }

	inline bool hasDiffuse() const { return m_hasDiffuse; }
private:
	const Texture* m_texture;
	const Texture* m_normalMap;
	const Texture* m_specMap;

	glm::vec4 m_modColour;

	float m_reflectivity;
	float m_specularIndex;

	bool m_reflections;
	bool m_hasDiffuse;

	void setDefaultTextures() {
		if (m_texture == nullptr) {
			m_texture = Texture::textureManager.getPointer("default_diff.png");
			m_hasDiffuse = false;
		} else {
			m_hasDiffuse = true;
		}
		if (m_normalMap == nullptr) {
			m_normalMap = Texture::textureManager.getPointer("default_normal.png");
		}
		if (m_specMap == nullptr) {
			m_specMap = Texture::textureManager.getPointer("default_spec.png");
		}
	}
};



