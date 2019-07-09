#include "Mesh.h"
#include <iostream>
#include "../Utils/OBJloader.h"


Mesh::Mesh(const Model& model):
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
	m_vao.Delete();
}


void Mesh::InitMesh(const Model& model)
{

	m_drawCount = model.indices.size();
	m_vao.Init();
	m_vao.Bind();
	m_vao.AttachBuffer(GL_ARRAY_BUFFER,  model.vertices.size() * sizeof(Vertex), GL_STATIC_DRAW, &model.vertices[0]);
	m_vao.AttachBuffer(GL_ELEMENT_ARRAY_BUFFER,  model.indices.size() * sizeof(unsigned int), GL_STATIC_DRAW, &model.indices[0]);

	// vertex positions
	m_vao.AddAttributef(0, 3, sizeof(Vertex), (void*)0);
	// vertex texture coords
	m_vao.AddAttributef(1, 2, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));
	// vertex normals
	m_vao.AddAttributef(2, 3, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex tangents
	m_vao.AddAttributef(3, 3, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	m_vao.UnBind();
}

void Mesh::Draw() const
{
	m_vao.Bind();
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);
	m_vao.UnBind();
}

std::vector<Vertex> Mesh::GetVertices() const
{
	return m_model.vertices;
}
std::vector<unsigned> Mesh::GetIndices() const
{
	return m_model.indices;
}

AnimatedMesh::AnimatedMesh(const Model& model, const std::vector<Bone*>& bones, const std::vector<VertexBoneData>& boneData)
{
	m_bones = bones;
	m_boneData = boneData;
	m_model = model;
	InitAnimatedMesh(m_model);
}

void AnimatedMesh::InitAnimatedMesh(const Model& model)
{
	Mesh::InitMesh(model);
	m_vao.Bind();
	m_vao.AttachBuffer(GL_ARRAY_BUFFER, m_boneData.size() * sizeof(VertexBoneData), GL_STATIC_DRAW, &m_boneData[0]);
	m_vao.AddAttributei(4, 4, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, m_IDs[0]));
	m_vao.AddAttributef(5, 4, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, m_weights[0]));
	m_vao.UnBind();
}

