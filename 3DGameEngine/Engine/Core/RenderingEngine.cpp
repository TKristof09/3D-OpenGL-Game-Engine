#include "RenderingEngine.h"
#include "GameObject.h"
#include "Input.h"
#include "..\Rendering\Lighting\ForwardAmbient.h"
#include "..\GameComponents\Lighting.h"


RenderingEngine::RenderingEngine()
    :
//   m_mainCamera(Camera(math::Vector3(0, 3, 10), math::Vector3(0, 0, -1), math::Vector3(0, 1, 0), 70.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f)),
    m_mainCamera(nullptr),
    m_ambientLight(math::Vector3(1, 0.05f, 0.05f)),
    m_activeLight(nullptr)
{
    glClearColor(0.3f, 0.3f, 0.3f, 0);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_CLAMP); //camera clipping prevention, i think
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}




void RenderingEngine::Render(const GameObject& object)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object.Render(ForwardAmbient::GetInstance(), this);

	glEnable(GL_BLEND); //enable blending the colors together
	glBlendFunc(GL_ONE, GL_ONE); //take existing color*1 and new color*1 == adding them together
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);



    for (const BaseLight* light : m_lights)
    {
        m_activeLight = light;
        object.Render(m_activeLight->GetShader(), this);
    }


	glDepthFunc(GL_LESS);
	glDepthMask(true);
	glDisable(GL_BLEND);
}
