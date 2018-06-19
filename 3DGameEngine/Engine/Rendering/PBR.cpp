#include "PBR.h"
#include "IrradianceShader.h"
#include "PrefilterShader.h"
#include "BRDFLUTShader.h"
#include "BasicShapes.h"

math::Matrix4x4 PBR::m_captureProjection = math::perspective(math::ToRadians(90.0f), 1.0f, 0.1f, 10.0f);;
math::Matrix4x4 PBR::m_captureViews[] = 
{
    //-x -y for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))),
    //+x -y for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))),
    //-y -z for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(1, 0, 0))),
    //+y +z for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(1, 0, 0))),
    //+z -y for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1))),
    //-z -y for up
    math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)))
};

unsigned int PBR::m_fbo = 0;
unsigned int PBR::m_rbo = 0;

Texture* PBR::ConvoluteIrradianceMap(Texture* environmentcubeMap, unsigned int size)
{
    TextureConfig config;
    config.wrapModeS = GL_CLAMP_TO_EDGE;
    config.wrapModeT = GL_CLAMP_TO_EDGE;
    config.target = GL_TEXTURE_CUBE_MAP;
    config.width = size;
    config.height = size;
    config.forFrameBuffer = true;
    Texture* irradianceMap = new Texture(config);
    if(m_fbo == 0)
        glGenFramebuffers(1, &m_fbo);
    if(m_rbo == 0)
        glGenRenderbuffers(1, &m_rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);



    IrradianceShader* irradianceShader = IrradianceShader::GetInstance();
    irradianceShader->Bind();
    irradianceShader->SetUniform("environmentMap", 0);
    irradianceShader->SetUniform("projection", m_captureProjection);

    environmentcubeMap->Bind();

    glViewport(0, 0, size, size);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    for (unsigned int i = 0; i < 6; ++i)
    {
        irradianceShader->SetUniform("view", m_captureViews[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap->GetID(), 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

    return irradianceMap;

}

Texture* PBR::PrefilterMap(Texture* environmentCubeMap, unsigned size)
{
    const unsigned int maxMipLevels = 5;
    TextureConfig config;
    config.wrapModeS = GL_CLAMP_TO_EDGE;
    config.wrapModeT = GL_CLAMP_TO_EDGE;
    config.target = GL_TEXTURE_CUBE_MAP;
    config.width = size;
    config.height = size;
    config.forFrameBuffer = true;
    config.maxMipMapLevels = maxMipLevels;

    Texture* prefilterMap = new Texture(config);

    if (m_fbo == 0)
        glGenFramebuffers(1, &m_fbo);
    if (m_rbo == 0)
        glGenRenderbuffers(1, &m_rbo);


    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    PrefilterShader* prefilterShader = PrefilterShader::GetInstance();
    prefilterShader->Bind();
    prefilterShader->SetUniform("environmentMap", 0);
    prefilterShader->SetUniform("projection", m_captureProjection);

    environmentCubeMap->Bind();

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = size * std::pow(0.5, mip);
        unsigned int mipHeight = size * std::pow(0.5, mip);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        prefilterShader->SetUniform("roughness", roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            prefilterShader->SetUniform("view", m_captureViews[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap->GetID(), mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            RenderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

    return prefilterMap;
}

Texture* PBR::GenerateBRDFLUT(unsigned size)
{
    TextureConfig textureConfig;
    textureConfig.wrapModeS = GL_CLAMP_TO_EDGE;
    textureConfig.wrapModeT = GL_CLAMP_TO_EDGE;
    textureConfig.forFrameBuffer = true;
    textureConfig.width = size;
    textureConfig.height = size;
    textureConfig.internalFormat = GL_RG16F;
    textureConfig.format = GL_RG;
    textureConfig.dataType = GL_FLOAT;
    Texture* LUT = new Texture(textureConfig);

    if (m_fbo == 0)
        glGenFramebuffers(1, &m_fbo);
    if (m_rbo == 0)
        glGenRenderbuffers(1, &m_rbo);


    BRDFLUTShader* lutShader = BRDFLUTShader::GetInstance();
    lutShader->Bind();
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
    glViewport(0, 0, size, size);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, LUT->GetID(), 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

    return LUT;
}