#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include "3DMath\3DMath.h"

class IntersectData
{
public:
    IntersectData(bool doesIntersect, const math::Vector3& direction):
    m_doesIntersect(doesIntersect),
    m_direction(direction){ }

    const math::Vector3& GetDirection() const
    {
        return m_direction;
    }

    bool GetDoesIntersect() const
    {
        return m_doesIntersect;
    }

private:
    math::Vector3 m_direction;
    bool m_doesIntersect;
};

#endif
