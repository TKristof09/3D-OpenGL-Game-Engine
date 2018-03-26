#include "Plane.h"



Plane Plane::Normalized() const
{
    float magnitude = math::length(m_normal);
    return Plane(m_normal / magnitude, m_distance / magnitude);
}

IntersectData Plane::IntersectSphere(const BoundingSphere& other) const
{
    float distanceFromSphereCenter = abs(math::dot(m_normal, other.GetCenter()) + m_distance);
    float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();

    return IntersectData(distanceFromSphere < 0, m_normal * distanceFromSphere);
}
