#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm\glm.hpp>
#include "Texture.h"
#include "..\Core\Color.h"

class Material
{
public:
	Material();
	Material(const float& specularIntensity, const float& specularExponent);
	Material(const Texture& texture, const float& specularIntensity, const float& specularExponent);
	~Material();
	
	inline const Texture* GetTexture() const { return &m_texture; };
	inline void SetTexture(const Texture& texture) { m_texture = texture; };
	inline const float* GetSpecularIntensity() const { return &m_specularIntensity; };
	inline void SetSpecularIntensity(const float& intensity) { m_specularIntensity = intensity; };
	inline const float* GetSpecularExponent() const { return &m_specularExponent; };
	inline void SetSpecularExponent(const float& exponent) { m_specularExponent = exponent; };

private:
	Texture m_texture;
	float m_specularIntensity;
	float m_specularExponent;
};

#endif // !MATERIAL_H
