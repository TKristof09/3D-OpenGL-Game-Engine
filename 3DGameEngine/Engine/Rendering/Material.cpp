
#include "Material.h"
#include <iostream>
static const Texture defaultTexture = Texture("defaultTexture.jpg");
static const Texture defaultNormal = Texture("defaultNormal.jpg");

Material::Material(const float& specularIntensity, const float& specularExponent) :
	m_defaultVector3(math::Vector3(1))
{
	m_floatMap["specularIntensity"] = specularIntensity;
	m_floatMap["specularExponent"] = specularExponent;
}

Material::Material(const Texture& diffuseTexture, const float& specularIntensity, const float& specularExponent) :
	m_defaultVector3(math::Vector3(1))
{
	m_textureMap["diffuse"] = const_cast<Texture*>(&diffuseTexture);
	m_floatMap["specularIntensity"] = specularIntensity;
	m_floatMap["specularExponent"] = specularExponent;
}

Material::~Material()
{
	
}
const Texture& Material::GetTexture(const std::string& name) const
	{
		auto it = m_textureMap.find(name);
		if (it != m_textureMap.end())
		{
			return *(it->second);
		}

		return defaultTexture;
	}

const Texture& Material::GetNormal(const std::string& name) const
{
	auto it = m_textureMap.find(name);
	if (it != m_textureMap.end())
	{
		return *(it->second);
	}

	return defaultNormal;
}

