#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class ModelToWorldTransform {
public:
	inline void translate(glm::vec3 translation) { m_translation = glm::translate(m_translation, translation); }
	inline void setTranslation(glm::vec3 translation) { m_translation = glm::translate(glm::mat4(), translation); }

	inline void rotate(float angle, const glm::vec3 axis) { m_rotation = glm::rotate(m_rotation, angle, axis); }
	inline void setRotation(float angle, const glm::vec3 axis) { m_rotation = glm::rotate(glm::mat4(), angle, axis); }
	inline void setRotation(glm::mat4 rotation) { m_rotation = rotation; }

	inline void scale(glm::vec3 scale) { m_scale = glm::scale(m_scale, scale); }
	inline void setScale(glm::vec3 scale) { m_scale = glm::scale(glm::mat4(), scale); }

	inline glm::mat4 getTransformationMatrix() { return m_translation * m_rotation * m_scale; }
private:
	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;
};



