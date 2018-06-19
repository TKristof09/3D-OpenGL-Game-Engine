#ifndef RADIANCEHDR_H
#define RADIANCEHDR_H
#include <string>
#include <GL/glew.h>
#include <3DMath/3DMath.h>
#include "Texture.h"

class RadianceHDRTexture{
public:
	RadianceHDRTexture(const std::string& fileName);
	~RadianceHDRTexture();
    void Bind(unsigned int unit = 0) const;
	Texture* ToCubeMap(unsigned int size);

private:
    Texture* m_texture;

	
};
#endif
