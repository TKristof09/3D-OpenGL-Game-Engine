#ifndef PBR_H
#define PBR_H
#include "Texture.h"
#include <3DMath/3DMath.h>

class PBR
{
public:
    static Texture* ConvoluteIrradianceMap(Texture* environmentCubeMap, unsigned int size);
    static Texture* PrefilterMap(Texture* environmentCubeMap, unsigned int size);
    static Texture* GenerateBRDFLUT(unsigned int size);

private:
    static math::Matrix4x4 m_captureProjection;
    static math::Matrix4x4 m_captureViews[6];
    static unsigned int m_fbo, m_rbo;
};


#endif

