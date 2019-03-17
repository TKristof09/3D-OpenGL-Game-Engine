#define STB_IMAGE_IMPLEMENTATION
#include <cassert>
#include <iostream>
#include "Texture.h"
#include "../Utils/stb_image.h"
#include "3DMath/3DMath.h"
#ifdef _DEBUG
int e;
#define CHECK_GL_ERROR e = glGetError(); if(e != 0) std::cout << "GL error: 0x" << std::hex << e << " file: " <<__FILE__ << " line: " << std::dec << __LINE__ <<std::endl
#else
#define CHECK_GL_ERROR
#endif

void GenTextures(TextureConfig* config, GLenum target);
int maxTextures;

Texture::Texture(TextureConfig config)
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextures);
	m_config = config;
	glGenTextures(1, &m_textureID);
	glBindTexture(config.target, m_textureID);

	switch (config.target)
	{
		case GL_TEXTURE_2D:
			GenTextures(&config, config.target);
			break;

		case GL_TEXTURE_CUBE_MAP:
		{
			glTexParameteri(config.target, GL_TEXTURE_WRAP_R, config.wrapModeR);
			for (unsigned int i = 0; i < 6; ++i)
			{
				GenTextures(&config, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
			}
			break;
		}
		default:
			break;
	}

	glTexParameteri(config.target, GL_TEXTURE_WRAP_S, config.wrapModeS);
	glTexParameteri(config.target, GL_TEXTURE_WRAP_T, config.wrapModeT);
	glTexParameterf(config.target, GL_TEXTURE_MAG_FILTER, config.magFilter);
	glTexParameteri(config.target, GL_TEXTURE_MIN_FILTER, config.minFilter);
	glTexParameteri(config.target, GL_TEXTURE_MAX_LEVEL, config.maxMipMapLevels - 1);
	glTexParameteri(config.target, GL_TEXTURE_BASE_LEVEL, 0);
	if (config.maxMipMapLevels > 1)
	{
		glGenerateMipmap(config.target);
	}
	
}
void GenTextures(TextureConfig* config, GLenum target)
{
	if (config->forFrameBuffer)
	{
		//glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, config->width, config->height);
		glTexImage2D(target, 0, config->internalFormat, config->width, config->height, 0, config->format, config->dataType, nullptr);
		CHECK_GL_ERROR;
	}
	else
	{
		int width, height, numComponents = 0;
		if(config->hdrFormat)
		{
			stbi_set_flip_vertically_on_load(config->flipOnLoad);
			float* imageData = stbi_loadf(config->path.c_str(), &width, &height, &numComponents, 0);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;

			//glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, width, height);
			CHECK_GL_ERROR;
			//glTexSubImage2D(config->target, 0, 0, 0, width, height, config->format, config->dataType, imageData);
			glTexImage2D(target, 0, config->internalFormat, width, height, 0, config->format, config->dataType, imageData);
			CHECK_GL_ERROR;

			stbi_image_free(imageData);
		}
		else
		{
            stbi_set_flip_vertically_on_load(config->flipOnLoad);
			stbi_uc* imageData = stbi_load(config->path.c_str(), &width, &height, &numComponents, 4);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;
			
			else
			{
				//glTexStorage2D(config->target, config->maxMipMapLevels, config->internalFormat, width, height);
				//CHECK_GL_ERROR;
				//glTexSubImage2D(config->target, 0, 0, 0, width, height, config->format, config->dataType, imageData);
				glTexImage2D(target, 0, config->internalFormat, width, height, 0, config->format, config->dataType, imageData);
				CHECK_GL_ERROR;
			}
			stbi_image_free(imageData);
		}
	}
}
Texture::Texture(const std::string& fileName)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(m_config.target, m_textureID);

	m_config.minFilter = GL_LINEAR;
    m_config.path = GetPath(fileName);
	
    GenTextures(&m_config, m_config.target);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int unit) const
{
	assert(unit >= 0 && unit < maxTextures);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(m_config.target, m_textureID);
}
