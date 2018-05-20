#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H

#include "3DMath/3DMath.h"
#include <vector>
#include <GL/glew.h>
#include "../Core/Color.h"
#include "../GameComponents/MeshRenderer.h"

class Mesh;
class Shader;
class RenderingEngine;

class DebugLineDrawer {
public:
	DebugLineDrawer() = default;
	~DebugLineDrawer();
	static void AddPoint(const math::Vector3& point);
	static void AddSegment(const math::Vector3& start, const math::Vector3& end);
	static void AddLine(const math::Vector3& direction);
	static void AddMesh(MeshRenderer* meshRenderer);
	static void Draw(RenderingEngine* renderingEngine);
	static void SetPointColor(const Color& color)
	{
		m_pointColor = color;
	}
	static void SetLineColor(const Color& color)
	{
		m_lineColor = color;
	}
	static void SetLineWidth(float width)
	{
		glLineWidth(width);
	}
	
private:
	static unsigned int VBO, VAO;

	static Color m_pointColor;
	static Color m_lineColor;
	static std::vector<MeshRenderer*> m_meshRenderers;
	static std::vector<math::Vector3> m_points;
	static std::vector<math::Vector3> m_lineVertices;
	static std::vector<unsigned int> m_indices;
	static Material m_mat;
};
#endif
