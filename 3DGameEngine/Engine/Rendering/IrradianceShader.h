#ifndef IRRADIANCE_SHADER
#define IRRADIANCE_SHADER
#include "Shader.h"
#include "../Engine/Utils/FileLoader.h"

class IrradianceShader : public Shader
{
public:
	static IrradianceShader* GetInstance()
	{
		static IrradianceShader instance;
		return &instance;
	}
	IrradianceShader()
	{
		AddShader(GetPath("Shaders/cubeMap"), GL_VERTEX_SHADER);
		AddShader(GetPath("Shaders/irradiance"), GL_FRAGMENT_SHADER);
	}
};

#endif
