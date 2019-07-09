#ifndef MESH_H
#define MESH_H
#define MAX_BONES (int)100

#include "3DMath/3DMath.h"
#include <GL/glew.h>
#include <vector>
#include "../Memory/VAO.h"
#include <iostream>
#include <map>

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
	math::Matrix4x4 finalTransform;
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
			sum += weight;
			index++;
			if(sum > 1)
				std::cout << "sum = " << sum << std::endl;
		}
	}
	unsigned int index;
    unsigned int m_IDs[NUM_BONES_PER_VERTEX];
	float sum;
    float m_weights[NUM_BONES_PER_VERTEX];
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
		: m_drawCount(0) { }
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
	VAO m_vao;
	unsigned int m_drawCount;
};

class AnimatedMesh : public Mesh
{
public:
	AnimatedMesh(const Model& model, const std::vector<Bone*>& bones, const std::vector<VertexBoneData>& boneData);
	void InitAnimatedMesh(const Model& model);
	const std::vector<Bone*>& GetBones() const
	{
		return m_bones;
	}
private:
	GLuint m_boneDataBuffer;
	std::vector<Bone*> m_bones;
	std::vector<VertexBoneData> m_boneData;
	std::map<std::string, unsigned int> m_boneMapping;
	math::Matrix4x4 m_globalInverse;
};

#endif // !MESH_H
