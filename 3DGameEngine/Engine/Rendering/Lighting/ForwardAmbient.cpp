#include "ForwardAmbient.h"
#include "..\Engine\Core\RenderingEngine.h"



ForwardAmbient::ForwardAmbient()
{
	AddShader(".\\res\\forward-ambient", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-ambient", GL_FRAGMENT_SHADER);
}

void ForwardAmbient::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine) const
{
	
	material.GetTexture("diffuse").Bind();
    const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("ambientIntensity", *renderingEngine->GetAmbientLight());
}
