#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <3DMath/3DMath.h>
//#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "btBulletDynamicsCommon.h"
#include "../GameComponents/GameComponent.h"
#include "Collider.h"

class Rigidbody : public GameComponent
{
	
public:
	
	Rigidbody(float mass, const math::Vector3& localInertia = math::Vector3(0))
	:m_mass(mass),
	 m_localInertia(localInertia),
	 m_btRigidBody(nullptr),
	 m_physicsEngine(nullptr)
	{
		
	}

	~Rigidbody();
	

	void SetKinematic(bool state)
	{
		m_btRigidBody->setMassProps(0, btVector3(0, 0, 0));
		m_btRigidBody->setFlags(m_btRigidBody->getFlags() | (btCollisionObject::CF_KINEMATIC_OBJECT & state));
	}

	btRigidBody* GetBtPointer() const
	{
		return m_btRigidBody;
	}

	void AddForce(const math::Vector3& force, const math::Vector3& relativePosition = math::Vector3(0))
	{
		m_btRigidBody->applyForce(force.ToBtVector3(), relativePosition.ToBtVector3());
	}

	void AddTorque(const math::Vector3& torque)
	{
		m_btRigidBody->applyTorque(torque.ToBtVector3());
	}


	void AddToPhysicsEngine(PhysicsEngine* physicsEngine) override;

	void AddToGameObjectCallback() override
	{
		RequireComponent<Collider>();
		m_btRigidBody = new btRigidBody(m_mass, reinterpret_cast<btMotionState*>(GetTransform()), GetGameObject()->GetComponent<Collider>()->GetBtCollisionShape(), m_localInertia.ToBtVector3());
		m_btRigidBody->setUserPointer(this);
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
	float m_mass;
	math::Vector3 m_localInertia;
	btRigidBody * m_btRigidBody;
	PhysicsEngine* m_physicsEngine;
};

#endif
