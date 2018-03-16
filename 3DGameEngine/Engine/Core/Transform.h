#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>


class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(0,0,0), const glm::quat& rotation = glm::quat(1,0,0,0), const glm::vec3& scale = glm::vec3(1, 1, 1)) :
        m_parent(nullptr),
		m_position(position),
		m_rotation(rotation),
        m_scale(scale)
	{};

    

    
	glm::mat4 GetModel()  const
	{
		glm::mat4 translationMatrix = glm::translate(m_position);

        glm::mat4 rotationMatrix = glm::toMat4(m_rotation);

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		return GetParentMatrix() * translationMatrix * rotationMatrix * scaleMatrix;
	};


	glm::vec3 GetPosition() const { return m_position; };
	glm::quat GetRotation() const { return m_rotation; };
	glm::vec3 GetScale() const { return m_scale; };
    
    glm::vec3 GetForward() const { return glm::normalize(m_rotation * glm::vec3(0, 0, -1)); };
    glm::vec3 GetUp() const { return glm::normalize(m_rotation * glm::vec3(0, 1, 0)); };
    glm::vec3 GetRight() const { return glm::normalize(m_rotation * glm::vec3(1, 0, 0)); };

	void SetPosition(const glm::vec3& position) { m_position = position; };
	void SetRotation(const glm::quat& rotation) { m_rotation = rotation; };
	void SetScale(const glm::vec3& scale) { m_scale = scale; };
    void SetParent(Transform* parent) { m_parent = parent; };

    void Rotate(const glm::quat& rotation)
    {
        m_rotation = glm::normalize(rotation * m_rotation);
    }

    void Rotate(float angle, const glm::vec3 axis)
    {
        Rotate(glm::quat(cos(angle / 2), axis.x * sin(angle / 2), axis.y * sin(angle / 2), axis.z * sin(angle / 2)));
    }

private:

    glm::mat4 GetParentMatrix() const
    {
        if (m_parent != nullptr)
        {
            return m_parent->GetModel();
        }
        else
        {
            return glm::mat4(1.0);
        }
    }

    Transform* m_parent;

	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;
};


#endif // !TRANSFORM_H


