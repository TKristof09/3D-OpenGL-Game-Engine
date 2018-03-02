#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <glm\glm.hpp>

class DirectionalLight
{
public: 
	DirectionalLight(const glm::vec3& color = glm::vec3(0, 0, 0), float intensity = 0, const glm::vec3& direction = glm::vec3(0, 0, 0)):
		m_color(color),
		m_intensity(intensity),
		m_direction(glm::normalize(direction))
	{};

	inline const glm::vec3* GetDirection() const { return &m_direction; };
	inline const glm::vec3* GetColor() const { return &m_color; };
	inline const float* GetIntensity() const { return &m_intensity; };

	inline void SetColor(const glm::vec3& color) { m_color = color; };
	inline void SetIntensity(float intensity) { m_intensity = intensity; };
	inline void SetDirection(const glm::vec3& direction) { m_direction = direction; };

private:
	glm::vec3 m_color;
	float m_intensity;
	glm::vec3 m_direction;

};

#endif // !DIRECTIONALLIGHT_H
