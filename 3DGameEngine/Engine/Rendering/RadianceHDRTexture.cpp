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

RadianceHDRTexture::RadianceHDRTexture(const std::string& fileName)
{
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
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
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

CubeMap* RadianceHDRTexture::ToCubeMap(unsigned int size)
{

	unsigned int fbo, rbo;
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//to cube map
	CubeMap* cubeMap = new CubeMap(size);

	math::Matrix4x4 captureProjection = math::perspective(math::ToRadians(90.0f), 1.0f, 0.1f, 10.0f);
	math::Matrix4x4 captureViews[] =
	{
		//+x -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))),
		//-x -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))),
		//+y +z for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(1, 0, 0))),
		//-y -z for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(1, 0, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0))),
		//+z -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1))),
		//-z -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1)))
	};

	// convert HDR equirectangular environment map to cubemap equivalent
	EquirectangularToCubeMap equirectangularToCube;
	equirectangularToCube.Bind();
	equirectangularToCube.SetUniform("equirectangularMap", 0);
	equirectangularToCube.SetUniform("projection", captureProjection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glViewport(0, 0, size, size); // don't forget to configure the viewport to the capture dimensions.
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	for (unsigned int i = 0; i < 6; ++i)
	{
		equirectangularToCube.SetUniform("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, *cubeMap->GetID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderCube(); // renders a 1x1 cube
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());
	return cubeMap;
}

CubeMap* RadianceHDRTexture::Convolute(CubeMap* cubeMap, unsigned int size)
{
	
	CubeMap* irradianceMap = new CubeMap(size);

	unsigned int fbo, rbo;
	
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, size, size);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	math::Matrix4x4 captureProjection = math::perspective(math::ToRadians(90.0f), 1.0f, 0.1f, 10.0f);
	math::Matrix4x4 captureViews[] =
	{
		//+x -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))), 
		//-x -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(1, 0, 0))),
		//+y +z for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(90), math::Vector3(1, 0, 0))),
		//-y -z for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(-90), math::Vector3(1, 0, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0))),
		//+z -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 1, 0)) * math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1))), 
		//-z -y for up
		math::ToMatrix4x4(math::Quaternion(math::ToRadians(180), math::Vector3(0, 0, 1))) 
	};

	IrradianceShader irradianceShader;
	irradianceShader.Bind();
	irradianceShader.SetUniform("environmentMap", 0);
	irradianceShader.SetUniform("projection", captureProjection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubeMap->GetID());

	glViewport(0, 0, size, size);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	for (unsigned int i = 0; i < 6; ++i)
	{
		irradianceShader.SetUniform("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, *irradianceMap->GetID(), 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderCube();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glViewport(0, 0, *Window::GetWidth(), *Window::GetHeight());

	return irradianceMap;

}
