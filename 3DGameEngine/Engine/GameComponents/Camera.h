#ifndef CAMERA_H
#define CAMERA_H

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

	math::Matrix4x4 GetViewProjection() const
	{
		return math::perspective(math::ToRadians(m_fov), m_aspect, m_zNear, m_zFar) * math::toMat4(math::conjugate(GetTransform().GetWorldRotation())) * math::translate(GetTransform().GetWorldPosition() * -1.0f);
	}

private:
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};
#endif