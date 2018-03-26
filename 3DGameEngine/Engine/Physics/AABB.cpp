#include "AABB.h"

IntersectData AABB::IntersectAABB(const AABB& other) const
{
    math::Vector3 distances1 = other.GetMinExtents() - m_maxExtents;
    math::Vector3 distances2 = m_minExtents - other.GetMaxExtents();

    math::Vector3 distances(math::max(distances1.x, distances2.x), math::max(distances1.y, distances2.y), math::max(distances1.z, distances2.z));

    float maxDistance = math::compMax(distances);

    return IntersectData(maxDistance < 0, distances);
}
