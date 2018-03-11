#include "Material.h"


Material::Material():
	m_color(glm::vec3(1,1,1)), m_texture(Texture()), m_specularIntensity(2), m_specularExponent(32){ }

Material::Material(const glm::vec3& color, const float& specularIntensity, const float& specularExponent):
	m_color(color), m_texture(Texture()), m_specularIntensity(specularIntensity), m_specularExponent(specularExponent) { }

Material::Material(const Texture& texture, const glm::vec3& color, const float& specularIntensity, const float& specularExponent):
	m_color(color), m_texture(texture), m_specularIntensity(specularIntensity), m_specularExponent(specularExponent){ }

Material::~Material()
{
	printf("material destructor called \n");
}

