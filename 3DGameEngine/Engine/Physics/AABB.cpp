#include "AABB.h"
#include "..\3DMath\3DMath.h"


AABB::~AABB()
{
}

IntersectData AABB::IntersectAABB(const AABB& other)
{
    math::Vector3 distance1 = other.GetMinExtents() - m_maxExtents;
    math::Vector3 distance2 = m_minExtents - other.GetMaxExtents();

    math::Vector3 distances = math::Vector3(math::max(distance1, distance2));
    float maxDistance = math::compMax(distances);

    return  IntersectData(maxDistance < 0, distances);
}
