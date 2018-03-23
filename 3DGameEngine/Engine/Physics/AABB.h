#ifndef AABB_H
#define AABB_H

#include "IntersectData.h"
#include "..\3DMath\3DMath.h"

class AABB
{
public:
    AABB(const math::Vector3& minExtents, const math::Vector3& maxExtents):
    m_minExtents(minExtents),
    m_maxExtents(maxExtents){ }
    ~AABB();

    IntersectData IntersectAABB(const AABB& other);

    const math::Vector3& GetMinExtents() const { return m_minExtents; }
    const math::Vector3& GetMaxExtents() const{ return m_maxExtents; }

private:
    const math::Vector3 m_minExtents;
    const math::Vector3 m_maxExtents;
};

#endif //!AABB_H