#ifndef FORWARD_DIRECTIONAL_H
#define FORWARD_DIRECTIONAL_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;
class DirectionalLight;

class ForwardDirectional : public Shader
{
public:
	ForwardDirectional();
	~ForwardDirectional() = default;

	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance;
		return &instance;
	}

	void Bind() const
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
	                    RenderingEngine* renderingEngine) const override;
	void SetUniform(std::string uniform, const DirectionalLight& directionalLight) const;
};


#endif // !FORWARD_AMBIENT_H
