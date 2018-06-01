#ifndef MESH_H
#define MESH_H

#include "3DMath\3DMath.h"
#include <GL\glew.h>
#include <vector>

// TODO make calculate normals for meshes without normals
struct Vertex
{

	math::Vector3 position;
	math::Vector2 textCoords;
	math::Vector3 normal;
	math::Vector3 tangent;
};

struct Model
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

class Mesh
{
public:
	//TODO mesh data structure
	Mesh()
		: m_vao(0),
		  m_vbo(0),
		  m_ebo(0),
		  m_drawCount(0) { } 
	Mesh(const Model& model);
	Mesh(const std::string& fn);
	~Mesh();

	void Draw() const;
	std::vector<Vertex> GetVertices() const;
	std::vector<unsigned int> GetIndices() const;
	unsigned int GetNumVertices() const
	{
		return m_model.vertices.size();
	}

	void InitMesh(const Model& model);

private:
	Model m_model;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	unsigned int m_drawCount;
};


#endif // !MESH_H
