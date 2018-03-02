#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

//#include "..\Core\GameObject.h"
#include "..\Camera.h"
#include "..\Rendering\Lighting\DirectionalLight.h"
#include "..\Rendering\Lighting\PointLight.h"
#include "..\Rendering\Lighting\SpotLight.h"
#include <vector>

class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();
	void Render(GameObject object);
	void SetCamera(const Camera& camera) { mainCamera = camera; };
	const Camera* GetMainCamera() const { return &mainCamera; };
	const glm::vec3* GetAmbientLight() const{ return &m_ambientLight; };
	const DirectionalLight* GetDirectionalLight() const { return &m_directional; };
    const PointLight* GetPointLight() const { return &m_point; };
    const SpotLight* GetSpotLight() const { return &m_spot; };
	void Input();

private:
	Camera mainCamera;
	glm::vec3 m_ambientLight;
	DirectionalLight m_directional;
    PointLight m_point;
    std::vector<PointLight> pLights;
    SpotLight m_spot;
};

#endif // !RENDERINGENGINE_H


