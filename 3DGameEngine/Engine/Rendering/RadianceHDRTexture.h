#ifndef RADIANCEHDR_H
#define RADIANCEHDR_H
#include <string>
#include <GL/glew.h>
#include "CubeMap.h"

class RadianceHDRTexture {
public:
	RadianceHDRTexture(const std::string& fileName);
	~RadianceHDRTexture();
	void Bind(unsigned int unit = 0) const;
	CubeMap* ToCubeMap(unsigned int size);
	CubeMap* Convolute(CubeMap* environmentMap, unsigned int size);
private:
	GLuint m_textureID;

	
};
#endif
