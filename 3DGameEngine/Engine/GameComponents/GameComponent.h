#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "..\Camera.h"
#include "..\Core\Transform.h"
#include "..\Rendering\Shader.h"

class GameComponent
{
public:
	virtual ~GameComponent() = default;

	virtual void SetGameObject() {};
	virtual void Input() {};
	virtual void Update() {};
	virtual void Render(const Transform& transform, Shader* shader) {};
};

#endif // !GAMECOMPONENT_H
