#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorldMt.h"
#include "BulletCollision/CollisionDispatch/btCollisionDispatcherMt.h"
#include "../GameComponents/Rigidbody.h"
#include "TriggerCollider.h"

static void TickCallback(btDynamicsWorld *world, btScalar timeStep);
class PhysicsEngine
{
public:

	PhysicsEngine(btCollisionConfiguration* collisionConfiguration, btCollisionDispatcherMt* dispatcher,
		btBroadphaseInterface* broadphase, btConstraintSolverPoolMt* solverPool)
		: m_gravity(math::Vector3(0,-10, 0)),
		  m_dispatcher(dispatcher),
		  m_bp(broadphase),
		  m_solverPool(solverPool),
		  m_collisionConfig(collisionConfiguration),
		  m_dynamicsWorld(nullptr)
	{
		
		m_dynamicsWorld = new btDiscreteDynamicsWorldMt(m_dispatcher, m_bp, m_solverPool, m_collisionConfig);
		m_dynamicsWorld->setInternalTickCallback(TickCallback, this);
		m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	}

	~PhysicsEngine()
	{
		
		for (Rigidbody* rb : m_rigidbodies)
		{
			delete rb;
		}
		
		delete m_dynamicsWorld;
		delete m_solverPool;
		delete m_bp;
		delete m_dispatcher;
		delete m_collisionConfig;

		m_rigidbodies.clear();
		m_triggerColliders.clear();
	}

    /**
     * \brief Reinitializes the engine to base state
     */
    void ReInit();

	void AddRigidbody(Rigidbody* rb);
	void AddTriggerCollider(TriggerCollider* collider);

	/**
	 * \brief Simulates the movements every object connected to the engine
	 * \param delta: time to simulate 
	 */
	void Simulate(float delta) const;


	/**
	 * \brief Callback for internal bullet simulation ticks
	 */
	void PhysicsTickCallback(btScalar timeStep);

	void SetGravity(const math::Vector3& gravVec)
	{
		m_gravity = gravVec;
		m_dynamicsWorld->setGravity(m_gravity.ToBtVector3());
	}

	math::Vector3 GetGravity() const
	{
		return m_gravity;
	}

	void Remove(TriggerCollider* collider)
	{
		m_dynamicsWorld->removeCollisionObject(collider->GetBtPointer());
		m_triggerColliders.erase(m_triggerColliders.begin() + collider->GetId());
	}

	void Remove(Rigidbody* rb)
	{
		m_rigidbodies[rb->GetId()] = nullptr;
		m_dynamicsWorld->removeRigidBody(rb->GetBtPointer());
	}

private:
	math::Vector3 m_gravity;
	std::vector<Rigidbody*> m_rigidbodies;
	std::vector<TriggerCollider*> m_triggerColliders;

	btCollisionDispatcherMt* m_dispatcher;
	btBroadphaseInterface* m_bp;
	btConstraintSolverPoolMt* m_solverPool;
	btCollisionConfiguration* m_collisionConfig;
	btDiscreteDynamicsWorldMt* m_dynamicsWorld;
	
};

void TickCallback(btDynamicsWorld* world, btScalar timeStep)
{
	PhysicsEngine* engine = static_cast<PhysicsEngine*>(world->getWorldUserInfo());
	engine->PhysicsTickCallback(timeStep);
}

#endif //!PHYSICSENGINE_H
