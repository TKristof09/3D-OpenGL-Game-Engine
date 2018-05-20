#ifndef FORWARD_AMBIENT_H
#define FORWARD_AMBIENT_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;

class ForwardAmbient : public Shader
{
public:
	ForwardAmbient();
	~ForwardAmbient() = default;

	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient instance;
		return &instance;
	}

	void Bind() const
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
	                    RenderingEngine* renderingEngine) const override;
};


#endif // !FORWARD_AMBIENT_H
