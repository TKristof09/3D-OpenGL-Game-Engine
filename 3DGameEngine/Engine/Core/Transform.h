#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>


class Transform
{
public:
	Transform(const glm::vec3& localPosition = glm::vec3(0,0,0), const glm::quat& localRotation = glm::quat(1,0,0,0), const glm::vec3& localScale = glm::vec3(1, 1, 1)) :
        m_parent(nullptr),
		m_localPosition(localPosition),
		m_localRotation(localRotation),
        m_localScale(localScale)
	{};

	inline glm::mat4 GetModel()  const
	{
		glm::mat4 translationMatrix = glm::translate(GetWorldPosition());

        glm::mat4 rotationMatrix = glm::toMat4(GetWorldRotation());

		glm::mat4 scaleMatrix = glm::scale(GetWorldScale());

		return translationMatrix * rotationMatrix * scaleMatrix;
	};

	const glm::vec3* GetLocalPosition() const { return &m_localPosition; };
	const glm::quat* GetLocalRotation() const { return &m_localRotation; };
	const glm::vec3* GetLocalScale() const { return &m_localScale; };
    glm::vec3 GetWorldPosition() const
    {
        if (m_parent)
            return m_localPosition + m_parent->GetWorldPosition();
        else
            return m_localPosition;
    };
    glm::quat GetWorldRotation() const
    {
        if (m_parent)
            return m_localRotation * m_parent->GetWorldRotation();
        else
            return m_localRotation;
    };
    glm::vec3 GetWorldScale() const
    {
        if (m_parent)
            return m_localScale * m_parent->GetWorldScale();
        else
            return m_localScale;
    };

    glm::vec3 GetForward() const { return GetWorldRotation() * glm::vec3(0,0,-1); };
    glm::vec3 GetRight() const { return GetWorldRotation() * glm::vec3(1, 0, 0); };
    glm::vec3 GetUp() const { return GetWorldRotation() * glm::vec3(0, 1, 0); };

	void SetLocalPosition(const glm::vec3& position) { this->m_localPosition = position; };
	void SetLocalRotation(const glm::quat& rotation) { this->m_localRotation = rotation; };
	void SetLocalScale(const glm::vec3& scale) { this->m_localScale = scale; };
    void SetParent(Transform* parent) { m_parent = parent; };

private:

    Transform* m_parent;

	glm::vec3 m_localPosition;
	glm::quat m_localRotation;
	glm::vec3 m_localScale;
};


#endif // !TRANSFORM_H


