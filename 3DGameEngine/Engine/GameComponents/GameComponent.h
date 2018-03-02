#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "..\Camera.h"
#include "..\Core\Transform.h"
#include "..\Rendering\Shader.h"
#include "..\Core\RenderingEngine.h"

class GameComponent
{
public:
	virtual ~GameComponent() = default;

	virtual void SetGameObject() {};
	virtual void Input() {};
	virtual void Update() {};
	virtual void Render(const Transform& transform, Shader* shader, RenderingEngine* renderingEngine) {};
};

#endif // !GAMECOMPONENT_H
