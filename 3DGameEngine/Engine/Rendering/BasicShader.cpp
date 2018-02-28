#include "BasicShader.h"



BasicShader::BasicShader()
{
	Shader();
	AddShader(".\\res\\basicShader", GL_VERTEX_SHADER);
	AddShader(".\\res\\basicShader", GL_FRAGMENT_SHADER);
	
}

void BasicShader::Update(const Transform& transform,/* const Camera& camera,*/ const Material& material)
{
	if (material.GetTexture() != NULL)
	{
		material.GetTexture()->Bind();
	}
	glm::mat4 model = GetRenderingEngine()->GetMainCamera()->GetViewProjection() * transform.GetModel();
	SetUniform("transform", model);
	SetUniform("color", *material.GetColor());
}

BasicShader::~BasicShader()
{

}
