#include "Rigidbody.h"
#include "../Physics/PhysicsEngine.h"

void Rigidbody::AddToPhysicsEngine(PhysicsEngine* physicsEngine)
{
	m_physicsEngine = physicsEngine;
	physicsEngine->AddRigidbody(this);
}
Rigidbody::~Rigidbody()
{
	m_physicsEngine->Remove(this);
	delete m_btRigidBody;
};

