#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"
#include "Material.h"
#include "Lighting\DirectionalLight.h"
#include "Lighting\PointLight.h"
#include "Lighting\Attenuation.h"
#include "Lighting\SpotLight.h"

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

class PhongShader : public Shader
{
public:
	PhongShader();
	~PhongShader();
	void Bind()
	{
		Shader::Bind();
	};
	
	void Update(const Transform& transform, const Camera& camera, const Material& material);
	void SetUniform(const GLchar* uniform, const Attenuation& attenuation);
	void SetUniform(const GLchar* uniform, const DirectionalLight& directionalLight);
	void SetUniform(const GLchar* uniform, const BaseLight& baseLight);
	void SetUniform(const GLchar* uniform, const PointLight& pointLight);
	void SetUniform(const GLchar* uniform, const SpotLight& spotLight);

	inline const glm::vec3* GetAmbientLight() const { return &m_ambientLight; };
	inline void SetAmbientLight(const glm::vec3& ambientLight) { m_ambientLight = ambientLight; };
	
	inline const DirectionalLight* GetDirectionalLight() const { return &m_directionalLight; };
	inline void SetDirectionalLight(const DirectionalLight& directionalLight) { m_directionalLight = directionalLight; };

	inline const PointLight* GetPointLights() const { return m_pointLights; };
	inline void SetPointLights(const PointLight* pointLights, int arraySize) 
	{
		if (arraySize > MAX_POINT_LIGHTS)
		{
			std::cout << "Max point lights is: " + MAX_POINT_LIGHTS << "But you entered: " + arraySize << "only the first " + MAX_POINT_LIGHTS << "items will be used from the array" << std::endl;
			arraySize = MAX_POINT_LIGHTS;
		}
		for (int i = 0; i < arraySize; i++)
		{
			m_pointLights[i] = pointLights[i];
		}
	};

	inline const SpotLight* GetSpotLights() const { return m_spotLights; };
	inline void SetSpotLights(const SpotLight* spotLights, int arraySize)
	{
		if (arraySize > MAX_SPOT_LIGHTS)
		{
			std::cout << "Max spot lights is: " + MAX_SPOT_LIGHTS << "But you entered: " + arraySize << "only the first " + MAX_POINT_LIGHTS << "items will be used from the array" << std::endl;
			arraySize = MAX_SPOT_LIGHTS;
		}
		for (int i = 0; i < arraySize; i++)
		{
			m_spotLights[i] = spotLights[i];
		}
	};

private:
	Material m_material;
	glm::vec3 m_ambientLight;
	DirectionalLight m_directionalLight;
	PointLight m_pointLights[MAX_POINT_LIGHTS];
	SpotLight m_spotLights[MAX_SPOT_LIGHTS];
};



#endif // !PHONGSHADER_H

