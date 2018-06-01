
#include "Material.h"
#include <iostream>


Material::Material(const float& specularIntensity, const float& specularExponent) :
	m_defaultTexture(Texture()),
	m_defaultVector3(math::Vector3(1))
{
	m_floatMap["specularIntensity"] = specularIntensity;
	m_floatMap["specularExponent"] = specularExponent;
}

Material::Material(const Texture& diffuseTexture, const float& specularIntensity, const float& specularExponent) :
	m_defaultTexture(Texture()),
	m_defaultVector3(math::Vector3(1))
{
	m_textureMap["diffuse"] = diffuseTexture;
	m_floatMap["specularIntensity"] = specularIntensity;
	m_floatMap["specularExponent"] = specularExponent;
}

Material::~Material()
{
	
}
