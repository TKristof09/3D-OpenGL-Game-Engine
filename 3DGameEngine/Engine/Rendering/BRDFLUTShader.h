#ifndef BRDFLUT_SHADER
#define BRDFLUT_SHADER
#include "Shader.h"

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
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\brdf", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\brdf", GL_FRAGMENT_SHADER);
	}
};

#endif
#pragma once
