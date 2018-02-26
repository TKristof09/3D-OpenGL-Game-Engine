#ifndef MESH_H
#define MESH_H

#include <string>

#include <glm\glm.hpp>
#include <GL\glew.h>
#include "..\OBJloader.h"
// TODO make calculate normals for meshes without normals
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& textCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->textCoord.x = textCoord.x;
		this->textCoord.y = 1 - textCoord.y;
		this->normal = normal;
		
	};
	inline const glm::vec3* GetPos() const { return &pos; };
	inline const glm::vec2* GetTextCoord() const { return &textCoord; };
	inline const glm::vec3* GetNormal() const { return &normal; };
	
private:
	glm::vec3 pos;
	glm::vec2 textCoord;
	glm::vec3 normal;
	
};

class Mesh
{
public:
	Mesh() {};
	Mesh(Vertex vertices[], unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	~Mesh();


	void Draw();

private:
	enum
	{
		POSITION_VB,
		TEXTCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	void InitMesh(const IndexedModel model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};


#endif // !MESH_H

