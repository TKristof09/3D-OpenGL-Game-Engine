#ifndef FORWARD_AMBIENT_H
#define FORWARD_AMBIENT_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;

class ForwardAmbient : public Shader
{
public:
	ForwardAmbient();
	~ForwardAmbient();
	static ForwardAmbient* GetInstance()
	{

		static ForwardAmbient instance;
		return &instance;
	}
	void Bind()
	{
		Shader::Bind();
	};
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) const override;
private:
};



#endif // !FORWARD_AMBIENT_H

