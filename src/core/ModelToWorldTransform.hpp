#pragma once

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class ModelToWorldTransform {
public:
	ModelToWorldTransform() : m_translation(0.0, 0.0, 0.0),
							  m_rotation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f))),
							  m_scale(1.0, 1.0, 1.0) {}
	inline void translate(const glm::vec3& translation) { m_translation += translation; }
	inline void translate(float distance, const glm::vec3& dir) { translate(distance * dir); }
	inline void setTranslation(const glm::vec3& translation) { m_translation = translation; }

	inline void rotate(float angle, const glm::vec3& axis) { rotate(glm::angleAxis(angle, axis)); }
	inline void rotate(const glm::quat& quat) { m_rotation = m_rotation * quat; }
	inline void setRotation(float angle, const glm::vec3& axis) { m_rotation = glm::angleAxis(angle, axis); }
	inline void setRotation(const glm::quat& quat) { m_rotation = quat; }

	inline void scale(const glm::vec3& scale) { m_scale *= scale; }
	inline void setScale(const glm::vec3& scale) { m_scale = scale; }

	inline const glm::vec3& getTranslation() const { return m_translation; }
	inline const glm::quat& getRotation() const { return m_rotation; }
	inline const glm::vec3& getScale() const { return m_scale; }

	inline const glm::mat4 getTranslationMatrix() const { return glm::translate(glm::mat4(), m_translation); }
	inline const glm::mat4 getRotationMatrix() const { return glm::mat4_cast(m_rotation); }
	inline const glm::mat4 getScaleMatrix() const { return glm::scale(glm::mat4(), m_scale); }

	inline glm::mat4 const getTransformationMatrix() const { return getTranslationMatrix()
																	* getRotationMatrix()
																	* getScaleMatrix(); }

	//Everything is actually moving around the camera
	//hence the reverse transforms
	inline glm::mat4 const getCameraMatrix() const { return getScaleMatrix()
	                                                        * glm::mat4_cast(glm::conjugate(m_rotation))
	                                                        * glm::translate(glm::mat4(), -m_translation); }

	//Transforms in model coordinates
	inline void moveForward(float distance) { translate(distance, m_rotation * glm::vec3(0.0f, 0.0f, -1.0f)); }
	inline void moveLeft(float distance) { translate(distance, m_rotation * glm::vec3(-1.0, 0.0f, 0.0f)); }
	inline void moveUp(float distance) { translate(distance, m_rotation * glm::vec3(0.0f, 1.0f, 0.0f)); }

	inline const glm::vec3 getForward() const { return m_rotation * glm::vec3(0.0f, 0.0f, -1.0f); }

	inline void turnUp(float angle) { rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f)); }
	inline void turnLeft(float angle) { rotate(angle, glm::conjugate(m_rotation) * glm::vec3(0.0f, -1.0f, 0.0f)); }

private:
	glm::vec3 m_translation;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};



