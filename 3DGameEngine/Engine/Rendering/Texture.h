#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL\glew.h>



class Texture
{
public:
	Texture(const std::string& path = "A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\defaultTexture.jpg");
	~Texture();
	void Bind(unsigned int unit = 0) const;

	std::string GetPath() const
	{
		return m_path;
	}

private:

	GLuint m_textureID;
	std::string m_path;
};

#endif // !TEXTTURE_H
