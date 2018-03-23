#include "BoundingSphere.h"


BoundingSphere::~BoundingSphere()
{}

IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere& other) const
{
    float radiusDistance = m_radius + other.GetRadius();
    math::Vector3 direction = other.GetCenter() - m_center;
    float centerDistance = math::length(direction);
    direction = direction / centerDistance;

    float distance = centerDistance - radiusDistance;

    return IntersectData(distance < 0, direction * distance);
}
