#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL\glew.h>

const static char* defaultTexture = ".\\res\\defaultTexture.jpg";

class Texture
{
public:
	Texture(const std::string& fileName = ".\\res\\defaultTexture.jpg");
	~Texture();
	void Bind (unsigned int unit = 0) const;

private:

	GLuint m_texture;

};

#endif // !TEXTTURE_H



