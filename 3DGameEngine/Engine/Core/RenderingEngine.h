#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H


#include <vector>
#include "Color.h"
#include "../Rendering/RadianceHDRTexture.h"

class GameObject;
class Camera;
class BaseLight;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine() = default;
	void Render(const GameObject& object);
	void AddLight(const BaseLight& light) { m_lights.push_back(&light); }
	//Temporary
    void Init();

	void SetMainCamera(Camera& camera) { m_mainCamera = &camera; };

	const Camera* GetMainCamera() const { return m_mainCamera; };

	const BaseLight* GetActiveLight() const { return m_activeLight; };
    //Temporary
	RadianceHDRTexture* GetBackground() const
	{
		return m_background;
	}

	Texture* envMap, *prefilterMap;
	Texture* brdfLUT;

private:
	RadianceHDRTexture* m_background;

	Camera* m_mainCamera;

	std::vector<const BaseLight*> m_lights;
	const BaseLight* m_activeLight;
};

#endif // !RENDERINGENGINE_H
