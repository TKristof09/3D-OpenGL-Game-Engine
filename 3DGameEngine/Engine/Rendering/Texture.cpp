#define STB_IMAGE_IMPLEMENTATION
#include <cassert>
#include <iostream>
#include "Texture.h"
#include "../Utils/stb_image.h"
#include <3DMath/3DMath.h>
#ifdef _DEBUG
int e;
#define CHECK_GL_ERROR e = glGetError(); if(e != 0) std::cout << "GL error: 0x" << std::hex << e << " file: " <<__FILE__ << " line: " << std::dec << __LINE__ <<std::endl
#else
#define CHECK_GL_ERROR
#endif

void GenTextures(TextureConfig* config);

Texture::Texture(TextureConfig config)
{
	m_config = config;
	glGenTextures(1, &m_textureID);
	glBindTexture(config.target, m_textureID);

	switch (config.target)
	{
		case GL_TEXTURE_2D:
			GenTextures(&config);
			break;

		case GL_TEXTURE_CUBE_MAP:
		{
			glTexParameteri(config.target, GL_TEXTURE_WRAP_R, config.wrapModeR);
			GenTextures(&config);
			break;
		}
		default:
			break;
	}

	glTexParameteri(config.target, GL_TEXTURE_WRAP_S, config.wrapModeS);
	glTexParameteri(config.target, GL_TEXTURE_WRAP_T, config.wrapModeT);
	glTexParameterf(config.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(config.target, GL_TEXTURE_MAX_LEVEL, config.maxMipMapLevels - 1);
	if (config.maxMipMapLevels > 1)
	{
		glTexParameteri(config.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glGenerateMipmap(config.target);
	}
	else
	{
		glTexParameteri(config.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}
void GenTextures(TextureConfig* config)
{
	if (config->forFrameBuffer)
	{
		int ret;
		glGetTexParameteriv(config->target, GL_TEXTURE_IMMUTABLE_FORMAT, &ret);
		std::cout << ret << std::endl;
		glTexParameteri(config->target, GL_TEXTURE_BASE_LEVEL, 0);
		glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, config->width, config->height);
		CHECK_GL_ERROR;
	}
	else
	{
		int width, height, numComponents = 0;
		if(config->hdrFormat)
		{
			stbi_set_flip_vertically_on_load(true);
			float* imageData = stbi_loadf(config->path.c_str(), &width, &height, &numComponents, 4);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;

			glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, width, height);
			CHECK_GL_ERROR;
			glTexSubImage2D(config->target, 0, 0, 0, width, height, config->format, config->dataType, imageData);
			CHECK_GL_ERROR;

			stbi_image_free(imageData);
		}
		else
		{
			stbi_uc* imageData = stbi_load(config->path.c_str(), &width, &height, &numComponents, 4);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;

			glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, width, height);
			CHECK_GL_ERROR;
			glTexSubImage2D(config->target, 0, 0, 0, width, height, config->format, config->dataType, imageData);
			CHECK_GL_ERROR;

			stbi_image_free(imageData);
		}
	}
}
Texture::Texture(const std::string& fileName)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	int width, height, numComponents;
	stbi_uc* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
	if (imageData == nullptr)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	CHECK_GL_ERROR;

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(m_config.target, m_textureID);
}
