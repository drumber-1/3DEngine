#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class ModelToWorldTransform {
public:
	ModelToWorldTransform() : m_translation(0.0, 0.0, 0.0),
							  m_rotation(0.0, 0.0, 0.0, 0.0),
							  m_scale(1.0, 1.0, 1.0) {}
	inline void translate(const glm::vec3& translation) { m_translation += translation; }
	inline void setTranslation(const glm::vec3& translation) { m_translation = translation; }

	inline void rotate(float angle, const glm::vec3& axis) { m_rotation = glm::rotate(m_rotation, angle, axis); }
	inline void setRotation(float angle, const glm::vec3& axis) { m_rotation = glm::rotate(glm::quat(), angle, axis); }
	inline void setRotation(const glm::quat& quat) { m_rotation = quat; }

	inline void scale(const glm::vec3& scale) { m_scale *= scale; }
	inline void setScale(const glm::vec3& scale) { m_scale = scale; }

	inline const glm::vec3& getTranslation() const { return m_translation; }
	inline const glm::quat& getRotation() const { return m_rotation; }
	inline const glm::vec3& getScale() const { return m_scale; }

	inline const glm::mat4 getTranslationMatrix() const { return glm::translate(glm::mat4(), m_translation); }
	inline const glm::mat4 getRotationMatrix() const { return glm::mat4_cast(m_rotation); }
	inline const glm::mat4 getScaleMatrix() const { return glm::scale(glm::mat4(), m_scale); }

	inline glm::vec3 getDirection() const { return glm::vec3(m_rotation.x, m_rotation.y, m_rotation.z); }

	inline glm::mat4 const getTransformationMatrix() const { return getTranslationMatrix()
																	* getRotationMatrix()
																	* getScaleMatrix(); }
private:
	glm::vec3 m_translation;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};



