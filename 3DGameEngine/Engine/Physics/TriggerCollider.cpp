#include "TriggerCollider.h"
#include "../Physics/PhysicsEngine.h"
#include "../Core/Transform.h"

TriggerCollider::~TriggerCollider() 
{
	m_physicsEngine->Remove(this);
	delete m_btGhostObject;
}

void TriggerCollider::AddToPhysicsEngine(PhysicsEngine* physicsEngine)
{
	m_physicsEngine = physicsEngine;
	m_btGhostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	m_btGhostObject->setWorldTransform(GetTransform()->ToBtTransform());
	physicsEngine->AddTriggerCollider(this);
}
