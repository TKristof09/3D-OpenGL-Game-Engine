#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

//#include "..\Core\GameObject.h"
#include "..\Camera.h"
#include "..\Rendering\Lighting\Lighting.h"
#include <vector>

class GameObject;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();
	void Render(GameObject object);
	void Input();
    void AddLight(const BaseLight& light) { m_lights.push_back(&light); };

    void SetCamera(const Camera& camera) { mainCamera = camera; };

	inline const Camera* GetMainCamera() const { return &mainCamera; };
	inline const glm::vec3* GetAmbientLight() const{ return &m_ambientLight; };
    inline const BaseLight& GetActiveLight() const { return *m_activeLight; };

private:
	Camera mainCamera;
	glm::vec3 m_ambientLight;

    std::vector<const BaseLight*> m_lights;
    const BaseLight* m_activeLight;

	DirectionalLight m_directional;
    PointLight m_point;
    std::vector<PointLight> pLights;
    SpotLight m_spot;
};

#endif // !RENDERINGENGINE_H


