#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL\glew.h>



class Texture
{
public:
	Texture(const std::string& fileName = "A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\defaultTexture.jpg");
	~Texture();
	void Bind (unsigned int unit = 0) const;

private:

	GLuint m_texture;

};

#endif // !TEXTTURE_H



