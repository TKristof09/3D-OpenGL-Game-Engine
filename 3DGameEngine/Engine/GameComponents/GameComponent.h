#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "..\Camera.h"
#include "..\Core\Transform.h"

class GameComponent
{
public:
	virtual ~GameComponent() = default;

	virtual void SetGameObject() {};
	virtual void Input() {};
	virtual void Update() {};
	virtual void Render(const Transform& transform, const Camera& camera) {};
};

#endif // !GAMECOMPONENT_H
