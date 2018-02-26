#include "PhongShader.h"
#include <glm\ext.hpp>


PhongShader::PhongShader()
{
	Shader();
	AddShader(".\\res\\phong", GL_VERTEX_SHADER);
	AddShader(".\\res\\phong", GL_FRAGMENT_SHADER);
}


PhongShader::~PhongShader()
{

}

void PhongShader::Update(const Transform& transform, const Camera& camera, Material& material)
{
	m_material = &material;
	if (m_material->GetTexture() != NULL)
	{
		m_material->GetTexture()->Bind();
	}
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	Shader::SetUniform("transform", transform.GetModel());
	Shader::SetUniform("projectedTransform", model);
	Shader::SetUniform("materialColor", *material.GetColor());
	Shader::SetUniform("specularIntensity", *material.GetSpecularIntensity());
	Shader::SetUniform("specularExponent", *material.GetSpecularExponent());
	Shader::SetUniform("eyePos", *camera.GetPos());

	Shader::SetUniform("ambientLight", m_ambientLight);
	SetUniform("directionalLight", m_directionalLight);
	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::string name = "pointLights[" + std::to_string(i) + "]";
		SetUniform(name.c_str(), m_pointLights[i]);
	}

	for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		std::string name = "spotLights[" + std::to_string(i) + "]";
		SetUniform(name.c_str(), m_spotLights[i]);
	}
}

void PhongShader::SetUniform(const GLchar* uniform, const Attenuation& attenuation)
{
	GLchar* exponent = new GLchar[strlen(uniform) + 9];
	strcpy(exponent, uniform);
	strcat(exponent, ".exponent");

	Shader::SetUniform(exponent, *attenuation.GetExponent());

	GLchar* linear = new GLchar[strlen(uniform) + 7];
	strcpy(linear, uniform);
	strcat(linear, ".linear");

	Shader::SetUniform(linear, *attenuation.GetLinear());

	GLchar* constant = new GLchar[strlen(uniform) + 9];
	strcpy(constant, uniform);
	strcat(constant, ".constant");

	Shader::SetUniform(constant, *attenuation.GetConstant());

}

void PhongShader::SetUniform(const GLchar* uniform, const BaseLight& baseLight)
{
	GLchar* color = new GLchar[strlen(uniform) + 6];
	strcpy(color, uniform);
	strcat(color, ".color");

	GLchar* intensity = new GLchar[strlen(uniform) + 10];
	strcpy(intensity, uniform);
	strcat(intensity, ".intensity");

	Shader::SetUniform(color, *baseLight.GetColor());
	Shader::SetUniform(intensity, *baseLight.GetIntensity());
}
void PhongShader::SetUniform(const GLchar* uniform, const DirectionalLight& directionalLight)
{
	GLchar* base = new GLchar[strlen(uniform) + 5];
	strcpy(base, uniform);
	strcat(base, ".base");

	GLchar* direction = new GLchar[strlen(uniform) + 10];
	strcpy(direction, uniform);
	strcat(direction, ".direction");

	SetUniform(base, *directionalLight.GetBase());
	Shader::SetUniform(direction, *directionalLight.GetDirection());
}

void PhongShader::SetUniform(const GLchar* uniform, const PointLight& pointLight)
{
	GLchar* base = new GLchar[strlen(uniform) + 5];
	strcpy(base, uniform);
	strcat(base, ".base");

	SetUniform(base, *pointLight.GetBase());

	GLchar* attenuation = new GLchar[strlen(uniform) + 12];
	strcpy(attenuation, uniform);
	strcat(attenuation, ".attenuation");

	SetUniform(attenuation, *pointLight.GetAttenuation());

	GLchar* range = new GLchar[strlen(uniform) + 6];
	strcpy(range, uniform);
	strcat(range, ".range");

	Shader::SetUniform(range, *pointLight.GetRange());

	GLchar* position = new GLchar[strlen(uniform) + 9];
	strcpy(position, uniform);
	strcat(position, ".position");

	Shader::SetUniform(position, *pointLight.GetPosition());
}

void PhongShader::SetUniform(const GLchar* uniform, const SpotLight& spotLight)
{
	GLchar* pointLight = new GLchar[strlen(uniform) + 11];
	strcpy(pointLight, uniform);
	strcat(pointLight, ".pointLight");

	SetUniform(pointLight, *spotLight.GetPointLight());


	GLchar* direction = new GLchar[strlen(uniform) + 10];
	strcpy(direction, uniform);
	strcat(direction, ".direction");

	Shader::SetUniform(direction, *spotLight.GetDirection());
	
	GLchar* range = new GLchar[strlen(uniform) + 7];
	strcpy(range, uniform);
	strcat(range, ".cutoff");

	Shader::SetUniform(range, *spotLight.GetCutoff());
}