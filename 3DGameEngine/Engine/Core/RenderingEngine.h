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
	void Init();;

	void SetMainCamera(Camera& camera) { m_mainCamera = &camera; };

	const Camera* GetMainCamera() const { return m_mainCamera; };
	Color GetAmbientLightColor() const { return m_ambientLightColor; };
	float GetAmbientLightIntensity() const { return m_ambientLightIntensity; };

	const BaseLight* GetActiveLight() const { return m_activeLight; };

	void SetAmbientLightColor(const Color& ambientLightColor)
	{
		m_ambientLightColor = ambientLightColor;
	}

	void SetAmbientLightIntensity(float ambientLightIntensity)
	{
		m_ambientLightIntensity = ambientLightIntensity;
	}


	RadianceHDRTexture* GetBackground() const
	{
		return m_background;
	}

	Texture* envMap, *prefilterMap;
	Texture* brdfLUT;

private:
	RadianceHDRTexture* m_background;

	Camera* m_mainCamera;

	Color m_ambientLightColor;
	float m_ambientLightIntensity;

	std::vector<const BaseLight*> m_lights;
	const BaseLight* m_activeLight;
};

#endif // !RENDERINGENGINE_H
