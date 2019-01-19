#ifndef MESH_H
#define MESH_H

#include "3DMath/3DMath.h"
#include <GL/glew.h>
#include <vector>

#define NUM_BONES_PER_VERTEX 4

// TODO make calculate normals for meshes without normals
struct Vertex
{

	math::Vector3 position;
	math::Vector2 textCoords;
	math::Vector3 normal;
	math::Vector3 tangent;
};

struct Bone
{
	unsigned int index;
	math::Matrix4x4 offsetMatrix;
};

struct VertexBoneData
{
	void AddData(unsigned int id, float weight)
	{
		if(index < NUM_BONES_PER_VERTEX)
		{
			m_IDs[index] = id;
			m_weights[index] = weight;
			index++;
		}
	}
private:
	unsigned int index;
    unsigned int m_IDs[NUM_BONES_PER_VERTEX];
    float m_weights[NUM_BONES_PER_VERTEX];
}

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
	virtual	~Mesh();

	void Draw() const;
	std::vector<Vertex> GetVertices() const;
	std::vector<unsigned int> GetIndices() const;
	unsigned int GetNumVertices() const
	{
		return m_model.vertices.size();
	}

	void InitMesh(const Model& model);

protected:
	Model m_model;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ebo;
	unsigned int m_drawCount;
};

class AnimatedMesh : public Mesh
{
public:
	AnimatedMesh(const Model& model);
	void InitAnimatedMesh(const Model& model);
	void AddBones(const std::vector<Bone>& bones)
	{
		m_bones = bones;
	}
	void AddBoneData(const std::vector<VertexBoneData>& boneData)
	{
		m_boneData = boneData;
	}
private:
	GLuint m_boneDataBuffer;
	std::vector<Bone> m_bones;
	std::vector<VertexBoneData> m_boneData;
};

#endif // !MESH_H
