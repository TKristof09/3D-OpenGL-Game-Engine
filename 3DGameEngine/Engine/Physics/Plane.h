#ifndef PLANE_H
#define PLANE_H
#include "3DMath\3DMath.h"
#include "IntersectData.h"
#include "BoundingSphere.h"

class Plane
{
public:
    Plane(const math::Vector3& normal, float distance):
    m_normal(normal),
    m_distance(distance){};
    Plane Normalized() const;
    IntersectData IntersectSphere(const BoundingSphere& other) const;

    const math::Vector3& GetNormal() const
    {
        return m_normal;
    }

    float GetDistance() const
    {
        return m_distance;
    }

private:
private:
    math::Vector3 m_normal;
    float m_distance;
};

#endif //!PLANE_H