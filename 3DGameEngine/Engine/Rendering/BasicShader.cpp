#include "BasicShader.h"



BasicShader::BasicShader()
{
	Shader();
	AddShader(".\\res\\basicShader", GL_VERTEX_SHADER);
	AddShader(".\\res\\basicShader", GL_FRAGMENT_SHADER);
	
}

void BasicShader::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine)
{
	if (material.GetTexture() != NULL)
	{
		material.GetTexture()->Bind();
	}
	glm::mat4 model = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	SetUniform("transform", model);
	SetUniform("color", *material.GetColor());
}

BasicShader::~BasicShader()
{

}
