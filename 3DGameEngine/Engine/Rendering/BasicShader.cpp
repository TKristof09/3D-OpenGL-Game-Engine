#include "BasicShader.h"



BasicShader::BasicShader()
{
	Shader();
	AddShader(".\\res\\basicShader", GL_VERTEX_SHADER);
	AddShader(".\\res\\basicShader", GL_FRAGMENT_SHADER);
	
}

void BasicShader::Update(const Transform& transform, const Camera& camera, Material material)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	SetUniform("transform", model);
	SetUniform("color", *material.GetColor());
}

BasicShader::~BasicShader()
{

}
