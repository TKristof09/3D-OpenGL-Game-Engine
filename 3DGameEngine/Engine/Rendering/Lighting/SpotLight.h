#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <glm\glm.hpp>
#include "BaseLight.h"
#include "Attenuation.h"

class SpotLight
{
public:
	SpotLight()
	{
		m_pointLight = PointLight();
		m_direction = glm::vec3(0,0,0);
		m_cutoff = 10;
		glm::vec3 m_position = glm::vec3(0, 0, 0);
	};
	SpotLight(const PointLight& pointLight, const glm::vec3& direction, const float& cutoff)
	{
		m_pointLight = pointLight;
		m_direction = direction;
		m_cutoff = cutoff;
	};

	inline const PointLight* GetPointLight() const { return &m_pointLight; };
	inline const glm::vec3* GetDirection() const { return &m_direction; };
	inline const float* GetCutoff() const { return &m_cutoff; };

	inline void SetPointLight(const PointLight& pointLight) { m_pointLight = pointLight; };
	inline void SetDirection(const glm::vec3& direction) { m_direction = direction; };
	inline void SetCutoff(const float& cutoff) { m_cutoff = cutoff; };

private:
	PointLight m_pointLight;
	glm::vec3 m_direction;
	float m_cutoff;

};

#endif // !SPOTLIGHT_H
