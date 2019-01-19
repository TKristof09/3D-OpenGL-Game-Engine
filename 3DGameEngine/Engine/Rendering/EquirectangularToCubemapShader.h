#ifndef EQUIRECTANGULAR_TO_CUBEMAP_SHADER
#define EQUIRECTANGULAR_TO_CUBEMAP_SHADER
#include "Shader.h"
#include "../Engine/Utils/FileLoader.h"

class EquirectangularToCubeMap : public Shader
{
public:
	static EquirectangularToCubeMap* GetInstance()
	{
		static EquirectangularToCubeMap instance;
		return &instance;
	}
	EquirectangularToCubeMap()
	{
		AddShader(GetPath("Shaders/cubeMap"), GL_VERTEX_SHADER);
		AddShader(GetPath("Shaders/equiToCubeMap"), GL_FRAGMENT_SHADER);
	}
};

#endif
