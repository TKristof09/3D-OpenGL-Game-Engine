#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "..\OBJloader.h"
// TODO make calculate normals for meshes without normals
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCoord, const glm::vec3& normal)
        :
		m_pos(pos),
		m_textCoord(textCoord.x, 1-textCoord.y),
		m_normal(normal)
		
        {};
	inline const glm::vec3* GetPos() const { return &m_pos; };
	inline const glm::vec2* GetTextCoord() const { return &m_textCoord; };
	inline const glm::vec3* GetNormal() const { return &m_normal; };
	
private:
	glm::vec3 m_pos;
	glm::vec2 m_textCoord;
	glm::vec3 m_normal;
	
};

class Mesh
{
public:
	Mesh()
        : m_vertexArrayObject(0),
          m_drawCount(0)
    {
    } ;
	Mesh(Vertex vertices[], unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	~Mesh();


	void Draw() const;

private:
	enum
	{
		POSITION_VB,
		TEXTCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	void InitMesh(IndexedModel model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};


#endif // !MESH_H

