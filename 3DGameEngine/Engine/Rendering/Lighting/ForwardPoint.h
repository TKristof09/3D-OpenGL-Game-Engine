#ifndef FORWARD_POINT_H
#define FORWARD_POINT_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;
class PointLight;
class Attenuation;

class ForwardPoint : public Shader
{
public:
	ForwardPoint();
	~ForwardPoint() = default;
	static ForwardPoint* GetInstance()
	{

		static ForwardPoint instance;
		return &instance;
	}
	void Bind() const
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) const override;
    void SetUniform(const GLchar* uniform, const PointLight& pointLight) const;
    void SetUniform(const GLchar* uniform, const Attenuation& attenuation) const;
};



#endif // !FORWARD_POINT_H

