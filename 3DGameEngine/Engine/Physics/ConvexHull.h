#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "../Rendering/Mesh.h"
#include "3DMath/3DMath.h"
#include "../GameComponents/Collider.h"

class ConvexHull : public Collider
{
public:
	ConvexHull(const Mesh& mesh)
	:Collider(TYPE_CONVEXHULL, new btConvexHullShape(), this)
	{
		btConvexHullShape* shape = static_cast<btConvexHullShape*>(GetBtCollisionShape());
		m_vertices.reserve(mesh.GetNumVertices());
		for (math::Vector3 vertex : mesh.GetVerticesPosition())
		{
			shape->addPoint(vertex.ToBtVector3());
			m_vertices.push_back(vertex);
		}
		shape->optimizeConvexHull();
	}

	std::vector<math::Vector3> GetVertices() const
	{
		return m_vertices;
	}

protected:
	int GetColliderType() override
	{
		return TYPE_CONVEXHULL;
	};
private:
	std::vector<math::Vector3> m_vertices;
};

#endif
