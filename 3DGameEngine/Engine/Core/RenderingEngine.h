#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H


#include <vector>
#include "Transform.h"
#include "..\3DMath\3DMath.h"

class GameObject;
class Camera;
class BaseLight;

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine() = default;
	void Render(const GameObject& object);
    void AddLight(const BaseLight& light) { m_lights.push_back(&light); };

    void SetMainCamera( Camera& camera) { m_mainCamera = &camera;};

	inline const Camera* GetMainCamera() const { return m_mainCamera; };
	inline math::Vector3 GetAmbientLight() const{ return m_ambientLight; };
    inline const BaseLight& GetActiveLight() const { return *m_activeLight; };

private:
	Camera* m_mainCamera;
	math::Vector3 m_ambientLight;

    std::vector<const BaseLight*> m_lights;
    const BaseLight* m_activeLight;
};

#endif // !RENDERINGENGINE_H


