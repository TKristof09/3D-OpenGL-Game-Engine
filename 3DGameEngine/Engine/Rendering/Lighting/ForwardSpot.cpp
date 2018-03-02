#include "ForwardSpot.h"



ForwardSpot::ForwardSpot()
{
    Shader();
    AddShader(".\\res\\forward-spot", GL_VERTEX_SHADER);
    AddShader(".\\res\\forward-spot", GL_FRAGMENT_SHADER);
}


ForwardSpot::~ForwardSpot()
{

}


void ForwardSpot::UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine)
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
    SetUniform("spotLight", *renderingEngine->GetSpotLight());
}

void ForwardSpot::SetUniform(const GLchar* uniform, const Attenuation& attenuation)
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

void ForwardSpot::SetUniform(const GLchar* uniform, const PointLight& pointLight)
{
    GLchar* color = new GLchar[strlen(uniform) + 1];
    strcpy(color, uniform);
    strcat(color, ".base.color");

    Shader::SetUniform(color, *pointLight.GetColor());

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

    Shader::SetUniform(position, *pointLight.GetPosition());
}

void ForwardSpot::SetUniform(const GLchar* uniform, const SpotLight& spotLight)
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