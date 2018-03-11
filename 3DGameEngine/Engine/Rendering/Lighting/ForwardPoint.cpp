#include "ForwardPoint.h"
#include "..\Engine\Core\RenderingEngine.h"


ForwardPoint::ForwardPoint()
{
    AddShader(".\\res\\forward-point", GL_VERTEX_SHADER);
    AddShader(".\\res\\forward-point", GL_FRAGMENT_SHADER);
}



void ForwardPoint::UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine) const
{
	if (material.GetTexture() != nullptr)
	{
		material.GetTexture()->Bind();
	}
    const glm::mat4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("specularIntensity", *material.GetSpecularIntensity());
	Shader::SetUniform("specularExponent", *material.GetSpecularExponent());
	Shader::SetUniform("eyePos", *renderingEngine->GetMainCamera()->GetPos());
	SetUniform("pointLight", *dynamic_cast<const PointLight*>(&renderingEngine->GetActiveLight()));
}

void ForwardPoint::SetUniform(const GLchar* uniform, const Attenuation& attenuation) const
{
    GLchar* exponent = new GLchar[strlen(uniform) + 9];
    strcpy(exponent, uniform);
    strcat(exponent, ".exponent");

    Shader::SetUniform(exponent, attenuation.GetExponent());

    GLchar* linear = new GLchar[strlen(uniform) + 7];
    strcpy(linear, uniform);
    strcat(linear, ".linear");

    Shader::SetUniform(linear, attenuation.GetLinear());

    GLchar* constant = new GLchar[strlen(uniform) + 9];
    strcpy(constant, uniform);
    strcat(constant, ".constant");

    Shader::SetUniform(constant, attenuation.GetConstant());

}

void ForwardPoint::SetUniform(const GLchar* uniform, const PointLight& pointLight) const
{
    GLchar* color = new GLchar[strlen(uniform) + 1];
    strcpy(color, uniform);
    strcat(color, ".base.color");

    Shader::SetUniform(color, pointLight.GetColor()->ToVec3());

    GLchar* intensity = new GLchar[strlen(uniform) + 15];
    strcpy(intensity, uniform);
    strcat(intensity, ".base.intensity");

    Shader::SetUniform(intensity, *pointLight.GetIntensity());

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

    Shader::SetUniform(position, *pointLight.GetTransform().GetPosition());
}
