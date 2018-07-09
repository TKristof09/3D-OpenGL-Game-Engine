#include "RenderingEngine.h"
#include "GameObject.h"
#include "Input.h"
#include "..\Rendering\Lighting\ForwardAmbient.h"
#include "..\GameComponents\Lighting.h"
#include "../Rendering/PBR.h"


RenderingEngine::RenderingEngine()
    : envMap(nullptr),
      prefilterMap(nullptr),
      brdfLUT(nullptr),
      m_background(nullptr),
      m_mainCamera(nullptr),
      m_activeLight(nullptr)
{
    //glClearColor(0.05f, 0.05f, 0.05f, 0.05f);
    glEnable(GL_DEPTH_CLAMP); //camera clipping prevention
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}


void RenderingEngine::ReInit()
{
    for (const BaseLight* light : m_lights)
    {
        delete light;
    }
    m_lights.clear();
    m_activeLight = nullptr;
    if (envMap)
        delete envMap;
    envMap = nullptr;
    if (prefilterMap)
        delete prefilterMap;
    prefilterMap = nullptr;
    if (brdfLUT)
        delete brdfLUT;
    brdfLUT = nullptr;
    if(m_background)
        delete m_background;
    m_background = nullptr;
    if(m_mainCamera)
        delete m_mainCamera;
    m_mainCamera = nullptr;
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
    m_background = new RadianceHDRTexture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Newport_Loft\\Newport_Loft_Ref.hdr");
	glDisable(GL_CULL_FACE);
	Texture* cubeMap = m_background->ToCubeMap(1024);
    envMap = PBR::ConvoluteIrradianceMap(cubeMap, 128);
	prefilterMap = PBR::PrefilterMap(cubeMap, 256);
	brdfLUT = PBR::GenerateBRDFLUT(512);
	glEnable(GL_CULL_FACE);
}
