#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"
#include "Material.h"
class BasicShader : public Shader
{
public:
	BasicShader();
	~BasicShader();
	static BasicShader* GetInstance()
	{
		static BasicShader instance;
		return &instance;
	}
	void Bind()
	{
		Shader::Bind();
	};
	void Update(const Transform& transform,/* const Camera& camera,*/ const Material &material) override;
};



#endif // !BASICSHADER_H

