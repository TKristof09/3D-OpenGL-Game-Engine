#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>


class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(0,0,0), const glm::vec3& rotation = glm::vec3(0,0,0), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale)
	{};

	inline glm::mat4 GetModel() const
	{
		glm::mat4 translationMatrix = glm::translate(m_position);
		glm::mat4 rotationXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotationYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotationZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

		return translationMatrix * rotationMatrix * scaleMatrix;
	};

	inline glm::vec3* GetPosition() { return &m_position; };
	inline glm::vec3* GetRotation() { return &m_rotation; };
	inline glm::vec3* GetScale() { return &m_scale; };

	inline void SetPos(const glm::vec3& position) { this->m_position = position; };
	inline void SetRot(const glm::vec3& rotation) { this->m_rotation = rotation; };
	inline void SetScale(const glm::vec3& scale) { this->m_scale = scale; };

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};


#endif // !TRANSFORM_H


