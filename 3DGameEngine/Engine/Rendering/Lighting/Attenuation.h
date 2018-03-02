#ifndef ATTENUATION_H
#define ATTENUATION_H

#include <glm\glm.hpp>

class Attenuation
{
public:
	Attenuation(const float& exponent = 0, const float& linear = 0, const float& constant = 0)
	{
		m_exponent = exponent;
		m_linear = linear;
		m_constant = constant;
	};
	inline const float* GetExponent() const { return &m_exponent; };
	inline const float* GetLinear() const { return &m_linear; };
	inline const float* GetConstant() const { return &m_constant; };

	inline void SetExponent(const float& exponent) { m_exponent = exponent; };
	inline void SetLinear(const float& linear) { m_linear = linear; };
	inline void SetConstant(const float& constant) { m_constant = constant; };

private:
	// exponent*x^2+linear*x+constant
	float m_exponent;
	float m_linear;
	float m_constant;
};
#endif // !ATTENUATION_H