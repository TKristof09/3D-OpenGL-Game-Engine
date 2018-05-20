#ifndef TRIGGERCOLLIDER_H
#define TRIGGERCOLLIDER_H

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include "../GameComponents/Collider.h"

class TriggerCollider : public Collider{
public:
	TriggerCollider(Collider* collider)
	:Collider(collider),
	 m_btGhostObject(new btGhostObject()),
	m_physicsEngine(nullptr)
	{
		m_btGhostObject->setCollisionShape(collider->GetBtCollisionShape());
	}
	~TriggerCollider();
	
	void AddToPhysicsEngine(PhysicsEngine* physicsEngine) override;
	
	btGhostObject* GetBtPointer() const
	{
		return m_btGhostObject;
	}

	void OnTriggerEnter(Collider* other) const
	{
		std::cout << ToString(other->GetTransform()->GetWorldPosition()) << std::endl;
	};


	void SetId(int id)
	{
		m_id = id;
	}

	int GetId() const
	{
		return m_id;
	}

private:
	int m_id;
	btGhostObject * m_btGhostObject;
	PhysicsEngine* m_physicsEngine;
	
};

#endif
