#include "DebugDrawer.h"
#include "DebugShader.h"

std::vector<math::Vector3> DebugLineDrawer::m_points = {};
std::vector<math::Vector3> DebugLineDrawer::m_lineVertices = {};
std::vector<unsigned int> DebugLineDrawer::m_indices = {};
unsigned int DebugLineDrawer::VAO = 0;
unsigned int DebugLineDrawer::VBO = 0;
Color DebugLineDrawer::m_pointColor(Color::White);
Color DebugLineDrawer::m_lineColor(Color::White);
std::vector<MeshRenderer*> DebugLineDrawer::m_meshRenderers = {};
Material DebugLineDrawer::m_mat = Material();

DebugLineDrawer::~DebugLineDrawer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void DebugLineDrawer::AddPoint(const math::Vector3& point)
{
	m_points.push_back(point);
}

void DebugLineDrawer::AddSegment(const math::Vector3& start, const math::Vector3& end)
{
	m_lineVertices.push_back(start);
	m_lineVertices.push_back(end);
}

void DebugLineDrawer::AddLine(const math::Vector3& direction)
{
	math::Vector3 dir = normalize(direction);
	m_lineVertices.push_back(-dir * 100000.0f);
	m_lineVertices.push_back(dir * 100000.0f);
}


void DebugLineDrawer::AddMesh(MeshRenderer* meshRenderer)
{
	m_meshRenderers.push_back(meshRenderer);
}


void DebugLineDrawer::Draw(RenderingEngine* renderingEngine)
{

	if(!m_points.empty())
	{
		m_mat.AddVector3("color", m_pointColor.ToVector3());
		glEnable(GL_POINT_SMOOTH);
		glPointSize(15);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, m_points.size() * sizeof(m_points[0]), &m_points[0],
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vector3), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		DebugShader::GetInstance()->Bind();
		DebugShader::GetInstance()->UpdateUniforms(Transform(), m_mat, renderingEngine);

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, m_points.size());
		glBindVertexArray(0);
		glPointSize(1);
		glDisable(GL_POINT_SMOOTH);
	}

	if (!m_lineVertices.empty())
	{
		m_mat.AddVector3("color", m_lineColor.ToVector3());
		glEnable(GL_LINE_SMOOTH);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, m_lineVertices.size() * sizeof(m_lineVertices[0]), &m_lineVertices[0],
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::Vector3), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		DebugShader::GetInstance()->Bind();
		DebugShader::GetInstance()->UpdateUniforms(Transform(), m_mat,renderingEngine);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, m_lineVertices.size());
		glBindVertexArray(0);
		glDisable(GL_LINE_SMOOTH);
	}

	if (!m_meshRenderers.empty())
	{
		//Draw the meshes wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		for (MeshRenderer* mesh : m_meshRenderers)
		{
			mesh->Render(DebugShader::GetInstance(), renderingEngine);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}
	
}
