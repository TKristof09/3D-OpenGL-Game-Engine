#include "Mesh.h"
#include <iostream>
#include "Shader.h"


Mesh::Mesh(const std::string& fileName)
{
	//TODO Switch to ASSIMP
	m_model = OBJModel(fileName).ToIndexedModel();
	InitMesh(m_model);
}

Mesh::Mesh(Vertex vertices[], const unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	

	for (unsigned int i = 0; i < numVertices; i++)
	{
		m_model.positions.push_back(*vertices[i].GetPosition());
		m_model.texCoords.push_back(*vertices[i].GetTextCoord());
		m_model.normals.push_back(*vertices[i].GetNormal());
	}
	for (unsigned int i = 0; i < numIndices; i++)
	{
		m_model.indices.push_back(indices[i]);
	}
	InitMesh(m_model);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void Mesh::InitMesh(const IndexedModel model)
{
	
	m_drawCount = m_model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.positions.size() * sizeof(m_model.positions[0]), &m_model.positions[0],
	             GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.positions.size() * sizeof(m_model.texCoords[0]), &m_model.texCoords[0],
	             GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, m_model.normals.size() * sizeof(m_model.normals[0]), &m_model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.indices.size() * sizeof(m_model.indices[0]), &m_model.indices[0],
	             GL_STATIC_DRAW);


	glBindVertexArray(0);
}

void Mesh::Draw() const
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

std::vector<math::Vector3> Mesh::GetVerticesPosition() const
{
	return m_model.positions;
}
std::vector<unsigned> Mesh::GetIndices() const
{
	return m_model.indices;
}


