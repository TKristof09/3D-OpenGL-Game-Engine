#ifndef BOX_H
#define BOX_H
#include "../GameComponents/Collider.h"

class Box : public Collider
{
public:
	explicit Box(const math::Vector3& halfExtents)
		: Collider(TYPE_BOX, new btBoxShape(halfExtents.ToBtVector3()), this),
		m_halfExtents(halfExtents)
	{}

	math::Vector3 GetHalfExtents() const
	{
		return m_halfExtents;
	}

	

protected:
	int GetColliderType() override
	{
		return TYPE_BOX;
	};

private:

	math::Vector3 m_halfExtents;

	
};
#endif
