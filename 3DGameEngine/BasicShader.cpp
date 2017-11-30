#include "BasicShader.h"



BasicShader::BasicShader()
{
	Shader::Shader();
	AddShader(".\\res\\basicShader", GL_VERTEX_SHADER);
	AddShader(".\\res\\basicShader", GL_FRAGMENT_SHADER);
}


BasicShader::~BasicShader()
{

}
