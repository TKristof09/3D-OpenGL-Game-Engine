#ifndef CUBEMAP_H
#define CUBEMAP_H
#include <GL/glew.h>

class CubeMap {
public:
	CubeMap(unsigned int size);
	~CubeMap();
	void Bind(unsigned int unit = 0) const;
	const GLuint* GetID() const
	{
		return &m_textureID;
	}
private:
	GLuint m_textureID;
	
};
#endif
