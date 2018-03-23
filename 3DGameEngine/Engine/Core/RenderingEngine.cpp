#include "RenderingEngine.h"
#include "Window.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"
#include "..\Rendering\Lighting\ForwardAmbient.h"
#include "..\GameComponents\Lighting.h"
#include <iostream>


RenderingEngine::RenderingEngine()
    :
//   m_mainCamera(Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f)),
    m_mainCamera(nullptr),
    m_ambientLight(glm::vec3(0.05f, 0.05f, 0.05f)),
    m_activeLight(nullptr)
{
    glClearColor(0, 0, 0, 0);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_CLAMP); //camera clipping prevention
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

void RenderingEngine::Input()
{
//	double deltaTime = Time::GetDelta();
//	if (Input::GetKeyDown(SDL_SCANCODE_UP))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetForward() * 5 * deltaTime);
//	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetRight() * 5 * deltaTime);
//	if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetForward() * -5 * deltaTime);
//	if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetRight() * -5 * deltaTime);
//	if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetUp() * 5 * deltaTime);
//	if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
//		m_mainCamera->GetTransform()->SetLocalPosition(m_mainCamera->GetTransform()->GetLocalPosition() + m_mainCamera->GetTransform()->GetUp() * -5 * deltaTime);
//	
//
//	if (Input::GetKeyDown(SDL_SCANCODE_W))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(deltaTime)), m_mainCamera->GetTransform()->GetRight()));
//	if (Input::GetKeyDown(SDL_SCANCODE_S))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(-deltaTime)), m_mainCamera->GetTransform()->GetRight()));
//	if (Input::GetKeyDown(SDL_SCANCODE_A))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(deltaTime)), m_mainCamera->GetTransform()->GetUp()));
//	if (Input::GetKeyDown(SDL_SCANCODE_D))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(-deltaTime)), m_mainCamera->GetTransform()->GetRight()));
//	if (Input::GetKeyDown(SDL_SCANCODE_Q))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(deltaTime)), m_mainCamera->GetTransform()->GetForward()));
//	if (Input::GetKeyDown(SDL_SCANCODE_E))
//		m_mainCamera->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(static_cast<float>(-deltaTime)), m_mainCamera->GetTransform()->GetForward()));
}

