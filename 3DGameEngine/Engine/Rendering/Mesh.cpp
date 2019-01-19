#include "Mesh.h"
#include <iostream>
#include "../Utils/OBJloader.h"


Mesh::Mesh(const Model& model):
m_vao(0),
m_vbo(0),
m_ebo(0),
m_drawCount(0)
{
	m_model = model;
	InitMesh(m_model);
}

Mesh::Mesh(const std::string& fn)
{
	IndexedModel m = OBJModel(fn).ToIndexedModel();
	Model m2;
	for (unsigned int i = 0; i < m.positions.size(); ++i)
	{
		Vertex v;
		v.position = m.positions[i];
		v.textCoords = m.texCoords[i];
		v.normal = m.normals[i];
		m2.vertices.push_back(v);
	}
	m2.indices = m.indices;
	m_model = m2;
	InitMesh(m_model);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
}


void Mesh::InitMesh(const Model& model)
{
	
	m_drawCount = model.indices.size();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(Vertex), &model.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));
	// vertex normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glBindVertexArray(0);
}

void Mesh::Draw() const
{
	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

std::vector<Vertex> Mesh::GetVertices() const
{
	return m_model.vertices;
}
std::vector<unsigned> Mesh::GetIndices() const
{
	return m_model.indices;
}

AnimatedMesh::AnimatedMesh(const Model& Model)
{
	m_model = model;
	InitAnimatedMesh(animatedModel);
}

void AnimatedMesh::InitAnimatedMesh(const Model& model)
{
	Mesh::InitMesh(model);	
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_boneDataBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_boneDataBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_boneData.size() * sizeof(VertexBoneData), &m_boneData[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribIPointer(4, 4, GL_INT, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, IDs[0]));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, weights[0]));
	glBindVertexArray(0);
}

