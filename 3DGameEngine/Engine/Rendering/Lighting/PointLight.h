#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm\glm.hpp>
#include "BaseLight.h"
#include "Attenuation.h"

class PointLight
{
public:
	PointLight()
	{
		m_base = BaseLight(glm::vec3(0,0,0), 0);
		m_attenuation = Attenuation();
		m_range = 10;
		glm::vec3 m_position = glm::vec3(0,0,0);
	};
	PointLight(const BaseLight& baseLight, const Attenuation& attenuation, const float& range, const glm::vec3& position)
	{
		m_base = baseLight;
		m_attenuation = attenuation;
		m_range = range;
		m_position = position;
	};

	inline const BaseLight* GetBase() const { return &m_base; };
	inline const Attenuation* GetAttenuation() const { return &m_attenuation; };
	inline const float* GetRange() const { return &m_range; };
	inline const glm::vec3* GetPosition() const { return &m_position; };

	inline void SetBase(const BaseLight& base) { m_base = base; };
	inline void SetAttenuation(const Attenuation& attenuation) { m_attenuation = attenuation; };
	inline void SetRange(const float& range) { m_range = range; };
	inline void SetPosition(const glm::vec3& position) { m_position = position; };

private:
	BaseLight m_base;
	Attenuation m_attenuation;
	float m_range;
	glm::vec3 m_position;

};

#endif // !POINTLIGHT_H
