#pragma once

#include <glm/glm.hpp>
#include <string>

#include "texture/Texture.hpp"

class Material {
public:
	Material(const Texture* m_texture,
			 glm::vec4 modColour = glm::vec4(1.0, 1.0, 1.0, 1.0),
			 float reflectivity = 1,
			 float specularIndex = 32) : m_texture(m_texture),
									    m_modColour(modColour),
									    m_reflectivity(reflectivity),
									    m_specularIndex(specularIndex) {}
	inline const Texture* getTexture() const { return m_texture; }
	inline const glm::vec4& getModColour() const { return m_modColour; }
	inline float getReflectivity() const { return m_reflectivity; }
	inline float getSpecularIndex() const { return m_specularIndex; }
private:
	const Texture* m_texture;
	glm::vec4 m_modColour;
	float m_reflectivity;
	float m_specularIndex;
};



