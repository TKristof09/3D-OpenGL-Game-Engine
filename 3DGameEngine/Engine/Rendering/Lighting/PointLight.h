#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm\glm.hpp>
#include "Attenuation.h"

class PointLight
{
public:
	PointLight():
		m_color(glm::vec3(0, 0, 0)),
		m_intensity(0),
		m_attenuation(Attenuation()),
		m_range(0),
		m_position(glm::vec3(0, 0, 0))
	{}
	PointLight(const glm::vec3& color, float intensity, const Attenuation& attenuation, const float& range, const glm::vec3& position) :
		m_color(color),
		m_intensity(intensity),
		m_attenuation(attenuation),
		m_range(range),
		m_position(position)
	{}

	inline const glm::vec3* GetColor() const { return &m_color; };
	inline const float* GetIntensity() const { return &m_intensity; };
	inline const Attenuation* GetAttenuation() const { return &m_attenuation; };
	inline const float* GetRange() const { return &m_range; };
	inline const glm::vec3* GetPosition() const { return &m_position; };

	inline void SetColor(const glm::vec3& color) { m_color = color; };
	inline void SetIntensity(float intensity) { m_intensity = intensity; };
	inline void SetAttenuation(const Attenuation& attenuation) { m_attenuation = attenuation; };
	inline void SetRange(const float& range) { m_range = range; };
	inline void SetPosition(const glm::vec3& position) { m_position = position; };

private:
	glm::vec3 m_color;
	float m_intensity;
	Attenuation m_attenuation;
	float m_range;
	glm::vec3 m_position;

};

#endif // !POINTLIGHT_H
