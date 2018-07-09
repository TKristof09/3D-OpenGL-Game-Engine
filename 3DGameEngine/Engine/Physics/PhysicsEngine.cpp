#include "PhysicsEngine.h"

void PhysicsEngine::ReInit()
{
    for (Rigidbody* rb : m_rigidbodies)
    {
        delete rb;
    }
    m_rigidbodies.clear();
    m_triggerColliders.clear();
}

void PhysicsEngine::AddRigidbody(Rigidbody* rb)
{
	rb->SetId(m_rigidbodies.size());
	m_rigidbodies.push_back(rb);
	m_dynamicsWorld->addRigidBody(rb->GetBtPointer());
}

void PhysicsEngine::AddTriggerCollider(TriggerCollider* collider)
{
	collider->SetId(m_triggerColliders.size());
	m_triggerColliders.push_back(collider);
	m_dynamicsWorld->addCollisionObject(collider->GetBtPointer());
}

void PhysicsEngine::Simulate(float delta) const
{
	m_dynamicsWorld->stepSimulation(delta);
}

void PhysicsEngine::PhysicsTickCallback(btScalar timeStep)
{
	for (TriggerCollider* collider :m_triggerColliders)
	{
		for (unsigned int i = 0; i < collider->GetBtPointer()->getNumOverlappingObjects(); ++i)
		{
			collider->OnTriggerEnter((Collider*)collider->GetBtPointer()->getOverlappingObject(i)->getUserPointer());
		}
	}
}
