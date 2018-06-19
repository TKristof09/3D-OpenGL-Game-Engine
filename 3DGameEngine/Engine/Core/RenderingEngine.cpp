#include "RenderingEngine.h"
#include "GameObject.h"
#include "Input.h"
#include "..\Rendering\Lighting\ForwardAmbient.h"
#include "..\GameComponents\Lighting.h"
#include "../Rendering/PBR.h"


RenderingEngine::RenderingEngine()
	:
	//   m_mainCamera(Camera(math::Vector3(0, 3, 10), math::Vector3(0, 0, -1), math::Vector3(0, 1, 0), 70.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f)),
	m_mainCamera(nullptr),
	m_ambientLightColor(Color::Black),
	m_ambientLightIntensity(0.0f),
	m_activeLight(nullptr)
{
	m_background = new RadianceHDRTexture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Newport_Loft\\Newport_Loft_Ref.hdr");
	//glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
	glEnable(GL_DEPTH_CLAMP); //camera clipping prevention
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDepthFunc(GL_LEQUAL);

	
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


	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glDisable(GL_BLEND);
}

void RenderingEngine::Init()
{
	glDisable(GL_CULL_FACE);
	Texture* cubeMap = m_background->ToCubeMap(1024);
    envMap = PBR::ConvoluteIrradianceMap(cubeMap, 128);
	prefilterMap = PBR::PrefilterMap(cubeMap, 256);
	brdfLUT = PBR::GenerateBRDFLUT(512);
	glEnable(GL_CULL_FACE);
}
