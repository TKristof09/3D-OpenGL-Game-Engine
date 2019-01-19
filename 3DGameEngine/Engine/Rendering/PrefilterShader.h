#ifndef PREFILTER_SHADER
#define PREFILTER_SHADER
#include "Shader.h"
#include "../Engine/Utils/FileLoader.h"

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
		AddShader(GetPath("Shaders/cubeMap"), GL_VERTEX_SHADER);
		AddShader(GetPath("Shaders/prefilter"), GL_FRAGMENT_SHADER);
	}
};

#endif
