#include "RadianceHDRTexture.h"
#include <iostream>
#include <cassert>
#include "3DMath/3DMath.h"
#include "../Utils/AssimpImporter.h"
#include "../Core/GameObject.h"
#include "EquirectangularToCubemapShader.h"
#include "BasicShapes.h"

RadianceHDRTexture::RadianceHDRTexture(const std::string& fileName)
{
    TextureConfig config;
    config.wrapModeS = GL_CLAMP_TO_EDGE;
    config.wrapModeT = GL_CLAMP_TO_EDGE;
    config.minFilter = GL_LINEAR;
    config.flipOnLoad = true;
    config.hdrFormat = true;
    config.internalFormat = GL_RGB16F;
    config.format = GL_RGB;
    config.dataType = GL_FLOAT;
    config.path = fileName;

    m_texture = new Texture(config);
}
RadianceHDRTexture::~RadianceHDRTexture()
{
    delete m_texture;
}

void RadianceHDRTexture::Bind(unsigned int unit) const
{
    m_texture->Bind(unit);
}


Texture* RadianceHDRTexture::ToCubeMap(unsigned int size)
{
    math::Matrix4x4 captureProjection = math::perspective(math::ToRadians(90.0f), 1.0f, 0.1f, 10.0f);
    math::Matrix4x4 captureViews[6];
    //+x -y for up
    captureViews[1] = ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0)));
    //-x -y for up
    captureViews[0] = ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0)));
    //+y +z for up
    captureViews[3] = ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(1, 0, 0)));
    //-y -z for up
    captureViews[2] = ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(1, 0, 0)));
    //+z -y for up
    captureViews[4] = ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)));
    //-z -y for up
    captureViews[5] = ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)));
    
    TextureConfig config; 
	config.target = GL_TEXTURE_CUBE_MAP;
	config.wrapModeS = GL_CLAMP_TO_EDGE;
	config.wrapModeT = GL_CLAMP_TO_EDGE;
	config.wrapModeR = GL_CLAMP_TO_EDGE;
	config.minFilter = GL_LINEAR;
	config.width = size;
	config.height = size;
	config.forFrameBuffer = true;
	config.internalFormat = GL_RGBA16F;
	config.format = GL_RGBA;
	config.dataType = GL_FLOAT;
	config.maxMipMapLevels = 5;
	Texture* cubeMap = new Texture(config);

	unsigned fbo, rbo;

	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// convert HDR equirectangular environment map to cubemap equivalent
	EquirectangularToCubeMap* equirectangularToCube = EquirectangularToCubeMap::GetInstance();
	equirectangularToCube->Bind();
	equirectangularToCube->SetUniform("equirectangularMap", 0);

	glViewport(0, 0, size, size);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	equirectangularToCube->SetUniform("projection", captureProjection);
	Bind();
	for (unsigned int i = 0; i < 6; ++i)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubeMap->GetID(), 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		equirectangularToCube->SetUniform("view", captureViews[i]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderCube();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());
	glGenerateTextureMipmap(cubeMap->GetID());
	return cubeMap;
}


