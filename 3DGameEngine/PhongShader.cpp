#include "PhongShader.h"



PhongShader::PhongShader()
{
	Shader();
	AddShader(".\\res\\phong", GL_VERTEX_SHADER);
	AddShader(".\\res\\phong", GL_FRAGMENT_SHADER);
}


PhongShader::~PhongShader()
{

}

void PhongShader::Update(const Transform& transform, const Camera& camera, const Material& material)
{
	m_material = material;
	if (m_material.GetTexture() != NULL)
	{
		m_material.GetTexture()->Bind();
	}
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	Shader::SetUniform("transform", transform.GetModel());
	Shader::SetUniform("projectedTransform", model);
	Shader::SetUniform("baseColor", *material.GetColor());
	Shader::SetUniform("ambientLight", ambientLight);
	SetUniform("directionalLight", directionalLight);	
}

void PhongShader::SetUniform(GLchar* uniform, const BaseLight& baseLight)
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
void PhongShader::SetUniform(GLchar* uniform, const DirectionalLight& directionalLight)
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
