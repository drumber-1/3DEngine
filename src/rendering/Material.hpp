#pragma once

#include <glm/glm.hpp>
#include <string>

class Material {
public:
	Material(const std::string& m_texture, glm::vec4 modColour = glm::vec4(1.0, 1.0, 1.0, 1.0)) : m_textureID(m_texture),
																					              m_modColour(modColour) {}

	inline std::string getTextureID() { return m_textureID; }
	inline glm::vec4 getModColour() { return m_modColour; }
private:
	std::string m_textureID;
	glm::vec4 m_modColour;
};



