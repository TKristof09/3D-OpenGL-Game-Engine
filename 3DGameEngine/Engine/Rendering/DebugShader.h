#ifndef DEBUGSHADER_H
#define DEBUGSHADER_H
#include "Shader.h"

class DebugShader : public Shader
{
public:
	DebugShader()
	{
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\debugLine", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\debugLine", GL_FRAGMENT_SHADER);
	};
	static DebugShader* GetInstance()
	{
		static DebugShader instance;
		return &instance;
	}
	void UpdateUniforms(const Transform& transform, const Material& material,RenderingEngine* renderingEngine) const override
	{

		math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
		SetUniform("MVP", MVP);
		SetUniform("color", material.GetVector3("color"));
	};
};

#endif
