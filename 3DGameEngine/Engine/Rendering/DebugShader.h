#ifndef DEBUGSHADER_H
#define DEBUGSHADER_H
#include "Shader.h"
#include "../Engine/Utils/FileLoader.h"

class DebugShader : public Shader
{
public:
	DebugShader()
	{
		AddShader(GetPath("Shaders/debugLine"), GL_VERTEX_SHADER);
		AddShader(GetPath("Shaders/debugLine"), GL_FRAGMENT_SHADER);
	};
	static DebugShader* GetInstance()
	{
		static DebugShader instance;
		return &instance;
	}
	void UpdateUniforms(const Transform& transform, const Material& material,RenderingEngine* renderingEngine, bool animated = false) const override
	{

		math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
		SetUniform("MVP", MVP);
		SetUniform("color", material.GetVector3("color"));
	};
};

#endif
