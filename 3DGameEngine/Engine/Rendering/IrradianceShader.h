#ifndef IRRADIANCE_SHADER
#define IRRADIANCE_SHADER
#include "Shader.h"

class IrradianceShader : public Shader
{
public:
	IrradianceShader()
	{
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\irradiance", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\irradiance", GL_FRAGMENT_SHADER);
	}
};

#endif
