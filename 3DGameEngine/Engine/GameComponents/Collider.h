#ifndef COLLIDER_H
#define COLLIDER_H

#include "3DMath/3DMath.h"
#include "../GameComponents/GameComponent.h"
#include <BulletCollision/CollisionShapes/btCollisionShape.h>


class Collider : public GameComponent
{
public:
	enum
	{
		TYPE_SPHERE,
		TYPE_BOX,
		TYPE_CONVEXHULL,

		TYPE_SIZE
	};


	Collider(Collider* collider)
		:m_type(collider->GetColliderType()),
		 m_btCollisionShape(collider->GetBtCollisionShape()){}
	
	~Collider() 
	{
		delete m_btCollisionShape;
	}
	
	int GetType() const { return m_type; };

	btCollisionShape* GetBtCollisionShape() const
	{
		return m_btCollisionShape;
	}
	
protected:
	Collider(int type, btCollisionShape* btCollisionShape, void* userPointer) :
		m_type(type),
		m_btCollisionShape(btCollisionShape)
	{
		if (userPointer)
			m_btCollisionShape->setUserPointer(userPointer);
		m_btCollisionShape->setMargin(0.001);
	}

	virtual int GetColliderType() { return NULL; }
private:
	int m_type;
	btCollisionShape* m_btCollisionShape;
};




#endif //!COLLIDER_H
