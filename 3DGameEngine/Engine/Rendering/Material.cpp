#include "Material.h"


Material::Material():
	m_texture(Texture()), m_specularIntensity(2), m_specularExponent(32){ }

Material::Material(const float& specularIntensity, const float& specularExponent):
	m_texture(Texture()), m_specularIntensity(specularIntensity), m_specularExponent(specularExponent) { }

Material::Material(const Texture& texture, const float& specularIntensity, const float& specularExponent):
	m_texture(texture), m_specularIntensity(specularIntensity), m_specularExponent(specularExponent){ }

Material::~Material()
{
	printf("material destructor called \n");
}

