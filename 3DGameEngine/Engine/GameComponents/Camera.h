#ifndef CAMERA_H
#define CAMERA_H

#include <glm\ext.hpp> // used to make vectors to string

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include "..\GameComponents\GameComponent.h"
#include "..\Core\RenderingEngine.h"


//enum Camera_Movement
//{
//	FORWARD,
//	BACKWARD,
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN
//};
// TODO maybe implement in a .cpp
class Camera : public GameComponent
{
public:
	Camera(const float fov, const float aspect, const float zNear, const float zFar):
		m_fov(fov),
		m_aspect(aspect),
		m_zNear(zNear),
		m_zFar(zFar)
		{}
			
    void AddToEngine(RenderingEngine* renderingEngine) override
	{
        renderingEngine->SetMainCamera(*this);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar) * glm::lookAt(GetTransform().GetPosition(), GetTransform().GetForward() + GetTransform().GetPosition(), glm::vec3(0,1,0));
	}

private:
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};
#endif