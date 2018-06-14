#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "../Core/Window.h"


struct TextureConfig
{
	GLenum target = GL_TEXTURE_2D;
	GLenum wrapModeS = GL_REPEAT;
	GLenum wrapModeT = GL_REPEAT;
	GLenum wrapModeR = GL_REPEAT;
	GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR;
	GLenum magFilter = GL_LINEAR;
	GLenum internalFormat = GL_RGBA8;
	GLenum format = GL_RGBA;
	GLenum dataType = GL_UNSIGNED_BYTE;

	bool forFrameBuffer = false;
	//only used for frame buffer textures
	unsigned width = *Window::GetWidth();
	unsigned height = *Window::GetHeight();

	bool hdrFormat = false;
	unsigned maxMipMapLevels = 1;

	std::string path = "A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\defaultTexture.jpg";
};

class Texture
{
public:
	Texture(TextureConfig config=TextureConfig());
	Texture(const std::string& fileName);
	~Texture();
	void Bind(unsigned int unit = 0) const;

	const TextureConfig* GetConfig() const
	{
		return &m_config;
	}

	GLuint GetID() const
	{
		return m_textureID;
	}

private:

	GLuint m_textureID;
	TextureConfig m_config;
};


#endif // !TEXTTURE_H
