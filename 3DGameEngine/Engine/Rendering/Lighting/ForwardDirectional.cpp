#include "ForwardDirectional.h"



ForwardDirectional::ForwardDirectional()
{
	Shader();
	AddShader(".\\res\\forward-directional", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-directional", GL_FRAGMENT_SHADER);

}

void ForwardDirectional::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine)
{
	if (material.GetTexture() != NULL)
	{
		material.GetTexture()->Bind();
	}
	glm::mat4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("specularIntensity", *material.GetSpecularIntensity());
	Shader::SetUniform("specularExponent", *material.GetSpecularExponent());
	Shader::SetUniform("eyePos", *renderingEngine->GetMainCamera()->GetPos());
	SetUniform("directionalLight", *renderingEngine->GetDirectionalLight());

}

ForwardDirectional::~ForwardDirectional()
{

}

void ForwardDirectional::SetUniform(const GLchar* uniform, const DirectionalLight& directionalLight)
{
	GLchar* color = new GLchar[strlen(uniform) + 11];
	strcpy(color, uniform);
	strcat(color, ".base.color");
	
    Shader::SetUniform(color, *directionalLight.GetColor());

    GLchar* intensity = new GLchar[strlen(uniform) + 15];
    strcpy(intensity, uniform);
    strcat(intensity, ".base.intensity");

    Shader::SetUniform(intensity, *directionalLight.GetIntensity());

	GLchar* direction = new GLchar[strlen(uniform) + 10];
	strcpy(direction, uniform);
	strcat(direction, ".direction");

	Shader::SetUniform(direction, *directionalLight.GetDirection());
}