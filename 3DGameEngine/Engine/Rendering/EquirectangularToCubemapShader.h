#ifndef EQUIRECTANGULAR_TO_CUBEMAP_SHADER
#define EQUIRECTANGULAR_TO_CUBEMAP_SHADER
#include "Shader.h"

class EquirectangularToCubeMap : public Shader
{
public:
	EquirectangularToCubeMap()
	{
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\equiToCubeMap", GL_VERTEX_SHADER);
		AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\equiToCubeMap", GL_FRAGMENT_SHADER);
	}
};

#endif
