#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

//#include "..\Core\GameObject.h"
#include "..\Camera.h"

class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();
	void Render(GameObject object);
	void SetCamera(const Camera& camera) { mainCamera = camera; };
	const Camera* GetMainCamera() const { return &mainCamera; };

private:
	Camera mainCamera;
};

#endif // !RENDERINGENGINE_H


