#pragma once

#include <glm/glm.hpp>
#include <string>

class Texture;

class Material {
public:
	Material(const Texture* m_texture, glm::vec4 modColour = glm::vec4(1.0, 1.0, 1.0, 1.0)) : m_texture(m_texture),
																							  m_modColour(modColour) {}
	inline const Texture* getTexture() const { return m_texture; }
	inline const glm::vec4& getModColour() const { return m_modColour; }
private:
	const Texture* m_texture;
	glm::vec4 m_modColour;
};



