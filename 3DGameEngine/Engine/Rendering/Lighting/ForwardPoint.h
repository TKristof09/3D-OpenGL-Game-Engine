#ifndef FORWARD_POINT_H
#define FORWARD_POINT_H

#include "..\Shader.h"
#include "..\Material.h"
#include "PointLight.h"
class ForwardPoint : public Shader
{
public:
	ForwardPoint();
	~ForwardPoint();
	static ForwardPoint* GetInstance()
	{

		static ForwardPoint instance;
		return &instance;
	}
	void Bind()
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) override;
    void SetUniform(const GLchar* uniform, const PointLight& pointLight);
    void SetUniform(const GLchar* uniform, const Attenuation& attenuation);
};



#endif // !FORWARD_POINT_H

