#ifndef CAMERA_H
#define CAMERA_H

#include "3DMath\3DMath.h"
#include "..\GameComponents\GameComponent.h"
#include "..\Core\RenderingEngine.h"

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
        // need to take conjugate because everything appears to rotate opposite to the camera
        const math::Matrix4x4 cameraRotation = math::toMat4(math::conjugate(GetTransform().GetWorldRotation()));
        // need to take the opposite here too because everything appears to move to the opposite direction than the camera
        const math::Matrix4x4 cameraPosition = math::translate(GetTransform().GetWorldPosition() * -1.0f);
        return math::perspective(math::ToRadians(m_fov), m_aspect, m_zNear, m_zFar) * cameraRotation * cameraPosition;
    }

private:
	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;
};
#endif