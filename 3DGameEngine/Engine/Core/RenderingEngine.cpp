#include "RenderingEngine.h"
#include "..\Rendering\BasicShader.h"
#include "Window.h"
#include "GameObject.h"


RenderingEngine::RenderingEngine():
mainCamera(Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)*Window::GetWidth() / (float)*Window::GetHeight(), 0.01f, 1000.0f))
{
	

	glClearColor(0.5f, 0.5f, 0.5f, 1);
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
	Shader* shader = BasicShader::GetInstance();
	shader->SetRenderingEngine(this);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	object.Render(shader);
}
