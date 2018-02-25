#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <glm\glm.hpp>
#include "BaseLight.h"

class DirectionalLight
{
public: 
	DirectionalLight(const BaseLight& base=BaseLight(glm::vec3(1,1,1), 1.0f), const glm::vec3& direction=glm::vec3(0,0,0))
	{
		m_base = base;
		m_direction = glm::normalize(direction);
	};

	inline const BaseLight* GetBase() const { return &m_base; };
	inline const glm::vec3* GetDirection() const { return &m_direction; };

	inline void SetBase(const BaseLight& base) { m_base = base; };
	inline void SetDirection(const glm::vec3& direction) { m_direction = direction; };

private:
	BaseLight m_base;
	glm::vec3 m_direction;

};

#endif // !DIRECTIONALLIGHT_H
