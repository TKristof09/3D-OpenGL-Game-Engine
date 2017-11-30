#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"
class BasicShader : public Shader
{
public:
	BasicShader();
	~BasicShader();
	void Bind()
	{
		Shader::Bind();
	};
	void Update(const Transform& transform, const Camera& camera)
	{
		Shader::Update(transform, camera);
	};
};



#endif // !BASICSHADER_H

