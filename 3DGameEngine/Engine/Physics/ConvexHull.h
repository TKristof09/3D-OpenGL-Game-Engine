#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "../Rendering/Mesh.h"
#include "3DMath/3DMath.h"
#include "../GameComponents/Collider.h"
#include "BulletCollision/CollisionShapes/btConvexHullShape.h"

class ConvexHull : public Collider
{
public:
	ConvexHull(const Mesh& mesh)
	:Collider(TYPE_CONVEXHULL, new btConvexHullShape(), this)
	{
		btConvexHullShape* shape = static_cast<btConvexHullShape*>(GetBtCollisionShape());
		m_vertices.reserve(mesh.GetNumVertices());
		for (Vertex vertex : mesh.GetVertices())
		{
			shape->addPoint(vertex.position.ToBtVector3());
			m_vertices.push_back(vertex.position);
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
