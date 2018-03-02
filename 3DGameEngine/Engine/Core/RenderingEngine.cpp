#include "RenderingEngine.h"
#include "..\Rendering\BasicShader.h"
#include "Window.h"
#include "GameObject.h"
#include "Input.h"
#include "Time.h"
#include "..\Rendering\Lighting\ForwardAmbient.h"
#include "..\Rendering\Lighting\ForwardDirectional.h"
#include "..\Rendering\Lighting\ForwardPoint.h"
#include "..\Rendering\Lighting\ForwardSpot.h"

RenderingEngine::RenderingEngine():
mainCamera(Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)*Window::GetWidth() / (float)*Window::GetHeight(), 0.01f, 1000.0f)),
m_ambientLight(glm::vec3(0.1f,0.1f,0.1f)),
m_directional(DirectionalLight(glm::vec3(244.0f / 255.0f, 150.0f / 255.0f, 28.0f / 255.0f), 0.1f, glm::vec3(1, -1, 0))),
m_point(PointLight(glm::vec3(1, 0, 0), 1, Attenuation(1, 0, 0), 100, glm::vec3(-2, 1, 0))),
m_spot(SpotLight(PointLight(glm::vec3(0, 0, 1), 10, Attenuation(1, 0, 0), 100, glm::vec3(2, 1, 0)), glm::vec3(0, -1, -3), cos(glm::radians(40.0f))))
{
	glClearColor(0, 0, 0, 0);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_CLAMP); //camera clipping prevention
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


    //just for fun
    float lightFieldStartX = -10;
    float lightFieldStartY = -10;
    float lightFieldStepX = 5;
    float lightFieldStepY = 5;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            pLights.push_back(PointLight(glm::vec3(1, 0, 0), 0.4f, Attenuation(1, 0, 0), 100, glm::vec3(lightFieldStartX + lightFieldStepX * i, 1, lightFieldStartY + lightFieldStepY * j)));
        }
    }
    m_point = pLights[0];
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

	object.Render(ForwardDirectional::GetInstance(), this);


    for (size_t i = 0; i < pLights.size(); i++)
    {
        m_point = pLights[i];
        object.Render(ForwardPoint::GetInstance(), this);
    }

    object.Render(ForwardSpot::GetInstance(), this);

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
