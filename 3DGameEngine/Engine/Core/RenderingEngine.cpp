#include "RenderingEngine.h"
#include "Window.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"


RenderingEngine::RenderingEngine():
mainCamera(Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)*Window::GetWidth() / (float)*Window::GetHeight(), 0.01f, 1000.0f)),
m_ambientLight(glm::vec3(0.05f,0.05f,0.05f))
{
	glClearColor(0, 0, 0, 0);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_CLAMP); //camera clipping prevention
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}


RenderingEngine::~RenderingEngine()
{

}

void RenderingEngine::Render(GameObject object)
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
	double deltaTime = Time::GetDelta();
	if (Input::GetKeyDown(SDL_SCANCODE_UP))
		mainCamera.Translate(FORWARD, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
		mainCamera.Translate(RIGHT, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
		mainCamera.Translate(BACKWARD, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
		mainCamera.Translate(LEFT, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
		mainCamera.Translate(UP, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
		mainCamera.Translate(DOWN, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
		std::cout << mainCamera.GetForward()->x << ";" << mainCamera.GetForward()->y << ";" << mainCamera.GetForward()->z << ";" << std::endl;



	if (Input::GetKeyDown(SDL_SCANCODE_W))
		mainCamera.RotateX(deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_S))
		mainCamera.RotateX(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_A))
		mainCamera.RotateY(deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_D))
		mainCamera.RotateY(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_Q))
		mainCamera.RotateZ(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_E))
		mainCamera.RotateZ(deltaTime);
}
