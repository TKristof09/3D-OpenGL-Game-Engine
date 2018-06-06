#ifndef IRRADIANCE_SHADER
#define IRRADIANCE_SHADER
#include "Shader.h"

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
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\cubeMap", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\irradiance", GL_FRAGMENT_SHADER);
	}
};

#endif
