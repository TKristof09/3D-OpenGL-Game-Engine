#ifndef MATERIAL_H
#define MATERIAL_H
#include "3DMath/3DMath.h"
#include <map>
#include "Texture.h"
#include "../Engine/Utils/FileLoader.h"


class Material
{
public:
	Material():
		m_defaultVector3(math::Vector3(1))
	{}

	Material(const float& specularIntensity, const float& specularExponent);
	Material(const Texture& texture, const float& specularIntensity, const float& specularExponent);
	~Material();

	void AddTexture(const std::string& name, Texture* texture)
	{
		m_textureMap[name] = texture;
	}

	const Texture& GetTexture(const std::string& name) const;
    const Texture& GetNormal(const std::string& name) const;

	void AddVector3(const std::string& name, const math::Vector3& vector)
	{
		m_vec3Map[name] = vector;
	}

	const math::Vector3& GetVector3(const std::string& name) const
	{
		auto it = m_vec3Map.find(name);
		if (it != m_vec3Map.end())
		{
			return it->second;
		}

		return m_defaultVector3;
	}

	void AddFloat(const std::string& name, const float value)
	{
		m_floatMap[name] = value;
	}

	float GetFloat(const std::string& name) const
	{
		auto it = m_floatMap.find(name);
		if (it != m_floatMap.end())
		{
			return it->second;
		}

		return 1;
	}


private:
	
	math::Vector3 m_defaultVector3;
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, math::Vector3> m_vec3Map;
	std::map<std::string, float> m_floatMap;
};

#endif // !MATERIAL_H
