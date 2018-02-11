#ifndef BASELIGHT_H
#define BASELIGHT_H

#include <glm\glm.hpp>

class BaseLight
{
public:
	BaseLight(const glm::vec3& color = glm::vec3(1,1,1), float intensity = 1.0f)
	{
		m_color = color;
		m_intensity = intensity;
	};

	inline const glm::vec3* GetColor() const { return &m_color; };
	inline const float* GetIntensity() const { return &m_intensity; };

	inline void SetColor(const glm::vec3& color) { m_color = color; };
	inline void SetIntensity(float intensity) { m_intensity = intensity; };
private:
	glm::vec3 m_color;
	float m_intensity;
};

#endif // !BASELIGHT_H
