#include "ForwardDirectional.h"
#include "..\Engine\Core\RenderingEngine.h"
#include "..\Engine\GameComponents\Lighting.h"


ForwardDirectional::ForwardDirectional()
{
	AddShader(".\\res\\forward-directional", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-directional", GL_FRAGMENT_SHADER);
}

void ForwardDirectional::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine) const
{
	material.GetTexture("diffuse").Bind();
    const glm::mat4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("specularIntensity", material.GetFloat("specularIntensity"));
	Shader::SetUniform("specularExponent", material.GetFloat("specularExponent"));
	Shader::SetUniform("eyePos", renderingEngine->GetMainCamera()->GetTransform().GetWorldPosition());
	SetUniform("directionalLight", *dynamic_cast<const DirectionalLight*>(&renderingEngine->GetActiveLight()));

}

void ForwardDirectional::SetUniform(const GLchar* uniform, const DirectionalLight& directionalLight) const
{
	GLchar* color = new GLchar[strlen(uniform) + 11];
	strcpy(color, uniform);
	strcat(color, ".base.color");
	
    Shader::SetUniform(color, directionalLight.GetColor()->ToVec3());

    GLchar* intensity = new GLchar[strlen(uniform) + 15];
    strcpy(intensity, uniform);
    strcat(intensity, ".base.intensity");

    Shader::SetUniform(intensity, *directionalLight.GetIntensity());

	GLchar* direction = new GLchar[strlen(uniform) + 10];
	strcpy(direction, uniform);
	strcat(direction, ".direction");

	Shader::SetUniform(direction, directionalLight.GetTransform().GetForward());

}