#ifndef RADIANCEHDR_H
#define RADIANCEHDR_H
#include <string>
#include <GL/glew.h>
#include <3DMath/3DMath.h>
#include "Texture.h"

class RadianceHDRTexture {
public:
	RadianceHDRTexture(const std::string& fileName);
	~RadianceHDRTexture();
	void Bind(unsigned int unit = 0) const;
	Texture* ToCubeMap(unsigned int size);
	Texture* ConvoluteIrradianceMap(Texture* environmentCubeMap, unsigned int size);
	Texture* PrefilterMap(Texture* environmentCubeMap, unsigned int size);
	Texture* GenerateBRDFLUT(unsigned int size);
private:
	GLuint m_textureID;
	math::Matrix4x4 m_captureProjection;
	math::Matrix4x4 m_captureViews[6];

	
};
#endif
