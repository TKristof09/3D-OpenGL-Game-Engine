#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>


class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(0,0,0), const glm::quat& rotation = glm::quat(1,0,0,0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{};

	inline glm::mat4 GetModel()  const
	{
		glm::mat4 translationMatrix = glm::translate(m_position);

        glm::mat4 rotationMatrix = glm::toMat4(m_rotation);

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		return translationMatrix * rotationMatrix * scaleMatrix;
	};

	inline const glm::vec3* GetPosition() const { return &m_position; };
	inline const glm::quat* GetRotation() const { return &m_rotation; };
	inline const glm::vec3* GetScale() const { return &m_scale; };
    glm::vec3 GetForward() const { return (m_rotation * glm::vec3(0,0,-1)); };
    glm::vec3 GetRight() const { return (m_rotation * glm::vec3(1, 0, 0)); };
    glm::vec3 GetUp() const { return (m_rotation * glm::vec3(0, 1, 0)); };

	inline void SetPosition(const glm::vec3& position) { this->m_position = position; };
	inline void SetRotation(const glm::quat& rotation) { this->m_rotation = rotation; };
	inline void SetScale(const glm::vec3& scale) { this->m_scale = scale; };

private:

	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};


#endif // !TRANSFORM_H


