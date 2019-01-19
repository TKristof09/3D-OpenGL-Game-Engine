#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "3DMath/3DMath.h"
#include "../GameComponents/Collider.h"
#include <BulletCollision/CollisionShapes/btSphereShape.h>

class BoundingSphere : public Collider
{
public:
	BoundingSphere(float radius):
		Collider(TYPE_SPHERE, new btSphereShape(radius), this),
		m_radius(radius) {};
	float GetRadius() const
	{
		return m_radius;
	}

protected:
	int GetColliderType() override
	{
		return TYPE_SPHERE;
	}

private:
	float m_radius;
};

#endif //!BOUNDINGSPHERE_H
