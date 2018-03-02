#include "ForwardAmbient.h"



ForwardAmbient::ForwardAmbient()
{
	Shader();
	AddShader(".\\res\\forward-ambient", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-ambient", GL_FRAGMENT_SHADER);

}

void ForwardAmbient::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine)
{
	if (material.GetTexture() != NULL)
	{
		material.GetTexture()->Bind();
	}
	glm::mat4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	SetUniform("MVP", MVP);
	SetUniform("ambientIntensity", *renderingEngine->GetAmbientLight());
}

ForwardAmbient::~ForwardAmbient()
{

}
