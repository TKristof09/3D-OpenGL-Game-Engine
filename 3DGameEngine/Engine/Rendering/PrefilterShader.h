#ifndef PREFILTER_SHADER
#define PREFILTER_SHADER
#include "Shader.h"

class PrefilterShader : public Shader
{
public:
	static PrefilterShader* GetInstance()
	{
		static PrefilterShader instance;
		return &instance;
	}
	PrefilterShader()
	{
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\cubeMap", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\prefilter", GL_FRAGMENT_SHADER);
	}
};

#endif
