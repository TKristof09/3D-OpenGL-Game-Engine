#ifndef INTERSECT_DATA_H
#define INTERSECT_DATA_H
#include "..\3DMath\3DMath.h"

class IntersectData
{
public: 
    IntersectData(bool doesIntersect, const math::Vector3& direction):
    m_doesIntersect(doesIntersect),
    m_direction(direction){}
    bool GetDoesIntersect() const { return m_doesIntersect; }
    float GetDistance() const { return math::length(m_direction); };
    const math::Vector3& GetDirection() const{ return m_direction; }
   
private:
    bool m_doesIntersect;
    math::Vector3 m_direction; //collision normal with length set to distance
};

#endif