#ifndef BRDFLUT_SHADER
#define BRDFLUT_SHADER
#include "Shader.h"
#include "../Engine/Utils/FileLoader.h"

class BRDFLUTShader : public Shader
{
public:
	static BRDFLUTShader* GetInstance()
	{
		static BRDFLUTShader instance;
		return &instance;
	}
	BRDFLUTShader()
	{
		AddShader(GetPath("Shaders/brdf"), GL_VERTEX_SHADER);
		AddShader(GetPath("Shaders/brdf"), GL_FRAGMENT_SHADER);
	}
};

#endif
#pragma once
