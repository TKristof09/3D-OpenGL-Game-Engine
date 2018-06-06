#define STB_IMAGE_IMPLEMENTATION
#include <cassert>
#include <iostream>
#include "Texture.h"
#include "../Utils/stb_image.h"

void GenTextures(TextureConfig* config, GLenum target);

Texture::Texture(TextureConfig config)
{
	m_config = config;
	glGenTextures(1, &m_textureID);
	glBindTexture(config.target, m_textureID);

	glTexParameteri(config.target, GL_TEXTURE_WRAP_S, config.wrapModeS);
	glTexParameteri(config.target, GL_TEXTURE_WRAP_T, config.wrapModeT);
	if (config.generateMipMaps)
	{
		glTexParameteri(config.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(config.target);
	}
	else
	{
		glTexParameteri(config.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameterf(config.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	switch (config.target)
	{
		case GL_TEXTURE_2D:
			GenTextures(&config, GL_TEXTURE_2D);
			break;

		case GL_TEXTURE_CUBE_MAP:
			for (unsigned int i = 0; i < 6; ++i)
			{
				GenTextures(&config, GL_TEXTURE_CUBE_MAP_POSITIVE_X+i);
			}
			break;
		default:
			break;
	}
	
	
}
void GenTextures(TextureConfig* config, GLenum target)
{
	if (config->forFrameBuffer)
	{
		glTexImage2D(target, 0, config->internalFormat, config->width, config->height, 0, config->format, config->dataType, nullptr);
	}
	else
	{
		int width, height, numComponents;
		if(config->hdrFormat)
		{
			stbi_set_flip_vertically_on_load(true);
			float* imageData = stbi_loadf(config->path.c_str(), &width, &height, &numComponents, 4);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;

			glTexImage2D(target, 0, config->internalFormat, width, height, 0, config->format, config->dataType, imageData);

			stbi_image_free(imageData);
		}
		else
		{
			stbi_uc* imageData = stbi_load(config->path.c_str(), &width, &height, &numComponents, 4);
			if (imageData == nullptr)
				std::cerr << "Texture loading failed for texture: " << config->path << std::endl;

			glTexImage2D(target, 0, config->internalFormat, width, height, 0, config->format, config->dataType, imageData);

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
