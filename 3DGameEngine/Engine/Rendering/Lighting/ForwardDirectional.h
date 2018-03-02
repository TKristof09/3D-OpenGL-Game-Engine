#ifndef FORWARD_DIRECTIONAL_H
#define FORWARD_DIRECTIONAL_H

#include "..\Shader.h"
#include "..\Material.h"
class ForwardDirectional : public Shader
{
public:
	ForwardDirectional();
	~ForwardDirectional();
	static ForwardDirectional* GetInstance()
	{

		static ForwardDirectional instance;
		return &instance;
	}
	void Bind()
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) override;
	void SetUniform(const GLchar* uniform, const DirectionalLight& directionalLight);
private:
};



#endif // !FORWARD_AMBIENT_H

