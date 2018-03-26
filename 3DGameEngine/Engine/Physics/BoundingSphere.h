#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "3DMath\3DMath.h"
#include "IntersectData.h"

class BoundingSphere
{
public:
    BoundingSphere(const math::Vector3& center, float radius):
    m_center(center),
    m_radius(radius){};

    IntersectData IntersectBoundingSphere(const BoundingSphere& other) const;

    math::Vector3 GetCenter() const
    {
        return m_center;
    }

    float GetRadius() const
    {
        return m_radius;
    }

private:
    math::Vector3 m_center;
    float m_radius;
};

#endif //!BOUNDINGSPHERE_H