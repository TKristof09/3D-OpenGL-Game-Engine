#include "RadianceHDRTexture.h"
#include "../Utils/stb_image.h"
#include <iostream>
#include <cassert>
#include <3DMath/3DMath.h>
#include "../Utils/AssimpImporter.h"
#include "../Core/GameObject.h"
#include "EquirectangularToCubemapShader.h"
#include "IrradianceShader.h"
#include "../Core/Window.h"
#include "PrefilterShader.h"
#include "BRDFLUTShader.h"

RadianceHDRTexture::RadianceHDRTexture(const std::string& fileName)
{
	m_captureProjection = math::perspective(math::ToRadians(90.0f), 1.0f, 0.1f, 10.0f);
	//+x -y for up
	m_captureViews[1] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0)));
	//-x -y for up
	m_captureViews[0] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0)));	
	//+y +z for up
	m_captureViews[3] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(1, 0, 0)));
	//-y -z for up
	m_captureViews[2] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(1, 0, 0)));
	//+z -y for up
	m_captureViews[4] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)));
	//-z -y for up
	m_captureViews[5] = math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)));
	
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	float *data = stbi_loadf(fileName.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load HDR image." << std::endl;
	}
}
RadianceHDRTexture::~RadianceHDRTexture()
{
	glDeleteTextures(1, &m_textureID);
}

void RadianceHDRTexture::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

unsigned int quadVAO = 0;
unsigned int quadVBO = 0;
/**
 * \brief Renders a 1x1 XY quad
 */
void RenderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
/**
 * \brief Renders a 1x1 cube
 */
void RenderCube()
{
	
	// initialize (if necessary)
	if (cubeVAO == 0)
	{
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void CreateCubeMap(unsigned int* id, unsigned int size)
{

	unsigned int irradianceMap;
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *id);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, size, size, 0,
			GL_RGB, GL_FLOAT, nullptr);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture* RadianceHDRTexture::ToCubeMap(unsigned int size)
{
	TextureConfig config;
	config.target = GL_TEXTURE_CUBE_MAP;
	config.width = size;
	config.height = size;
	config.forFrameBuffer = true;
	config.internalFormat = GL_RGB16F;
	config.format = GL_RGB;
	config.dataType = GL_FLOAT;
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
	equirectangularToCube->SetUniform("projection", m_captureProjection);
	Bind();

	glViewport(0, 0, size, size);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	for (unsigned int i = 0; i < 6; ++i)
	{
		equirectangularToCube->SetUniform("view", m_captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubeMap->GetID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderCube();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

	return cubeMap;
}

Texture* RadianceHDRTexture::ConvoluteIrradianceMap(Texture* environmentcubeMap, unsigned int size)
{
	TextureConfig config;
	config.target = GL_TEXTURE_CUBE_MAP;
	config.width = size;
	config.height = size;
	config.forFrameBuffer = true;
	Texture* irradianceMap = new Texture(config);

	unsigned int fbo, rbo;
	
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	

	IrradianceShader* irradianceShader = IrradianceShader::GetInstance();
	irradianceShader->Bind();
	irradianceShader->SetUniform("environmentMap", 0);
	irradianceShader->SetUniform("projection", m_captureProjection);

	environmentcubeMap->Bind();

	glViewport(0, 0, size, size);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	for (unsigned int i = 0; i < 6; ++i)
	{
		irradianceShader->SetUniform("view", m_captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap->GetID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderCube();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

	return irradianceMap;

}

Texture* RadianceHDRTexture::PrefilterMap(Texture* environmentCubeMap, unsigned size)
{
	TextureConfig config;
	config.target = GL_TEXTURE_CUBE_MAP;
	config.width = size;
	config.height = size;
	config.forFrameBuffer = true;
	config.generateMipMaps = true;

	Texture* prefilterMap = new Texture(config);

	unsigned int fbo, rbo;

	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	PrefilterShader* prefilterShader = PrefilterShader::GetInstance();
	prefilterShader->Bind();
	prefilterShader->SetUniform("environmentMap", 0);
	prefilterShader->SetUniform("projection", m_captureProjection);
	
	environmentCubeMap->Bind();

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	const unsigned int maxMipLevels = 5;
	for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
	{
		// reisze framebuffer according to mip-level size.
		unsigned int mipWidth = 128 * std::pow(0.5, mip);
		unsigned int mipHeight = 128 * std::pow(0.5, mip);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
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
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

	return prefilterMap;
}

Texture* RadianceHDRTexture::GenerateBRDFLUT(unsigned size)
{
	TextureConfig textureConfig;
	textureConfig.wrapModeS = GL_CLAMP_TO_EDGE;
	textureConfig.wrapModeT = GL_CLAMP_TO_EDGE;
	textureConfig.forFrameBuffer = true;
	textureConfig.width = size;
	textureConfig.height = size;
	Texture* LUT = new Texture(textureConfig);

	unsigned int fbo, rbo;

	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);


	BRDFLUTShader* lutShader = BRDFLUTShader::GetInstance();
	lutShader->Bind();
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glViewport(0, 0, size, size);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, LUT->GetID(), 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

	return LUT;
}
