#include "AssimpTestGame.h"

#include "Utils/AssimpImporter.h"
#include "GameComponents/FreeLook.h"
#include "GameComponents/FreeMove.h"
#include "Core/Window.h"
#include "Utils/OBJloader.h"
#include "GameComponents/Lighting.h"
#include "Rendering/RadianceHDRTexture.h"

void AssimpTestGame::Init()
{
	
	auto cameraOBJ = new GameObject("camera");
	auto dLight = new GameObject("dLight");
	//--------------------------------------------------------------------------------------------------------------------------------------
	//Camera
	//--------------------------------------------------------------------------------------------------------------------------------------
	
	cameraOBJ->AddComponent(new Camera(
		60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
	cameraOBJ->GetTransform()->SetPosition(math::Vector3(0, 0, 5));
	cameraOBJ->AddComponent(new FreeLook());
	cameraOBJ->AddComponent(new FreeMove());
	AddToScene(cameraOBJ);
	
	RadianceHDRTexture* hdr = new RadianceHDRTexture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Arches_E_PineTree\\Arches_E_PineTree_3k.hdr");
	CubeMap* cubemap = hdr->ToCubeMap(512);
	CubeMap* irradiancemap = hdr->Convolute(cubemap, 64);
	AssimpImporter importer;
	GameObject* go = importer.ImportFile("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\sphere.obj");
	//go->GetTransform()->Rotate(math::ToRadians(-90.0f), math::Vector3(1, 0, 0));
	MeshRenderer* mr = go->GetChild(0)->GetComponent<MeshRenderer>();
	//go->GetChild(0)->GetTransform()->SetScale(math::Vector3(5));
	Material* material1 = mr->material;
	material1->AddTexture("albedo", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\rustediron2_basecolor.png"));
	material1->AddTexture("normal", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\rustediron2_normal.png"));
	material1->AddTexture("metallic", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\rustediron2_metallic.png"));
	material1->AddTexture("rougness", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\rustediron2_roughness.png"));
	//material1->AddVector3("color", Color::White.ToVector3());
	//material1->AddTexture("diffuse", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\checkerboard.png"));
	//material1->AddTexture("specular", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\checkerboard - specular.jpg"));
	//material1->AddFloat("specularExponent", 32);


	//MeshRenderer* mr2 = go->GetChild(0)->GetChild(0)->GetChild(0)->GetChild(0)->GetComponent<MeshRenderer>();
	//Material* material2 = mr->material;
	//material2->AddTexture("diffuse", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\checkerboard.png"));
	//material2->AddTexture("specular", new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\checkerboard - specular.jpg"));
	//material2->AddFloat("specularExponent", 32);

    //--------------------------------------------------------------------------------------------------------------------------------------
	//Lights
	//--------------------------------------------------------------------------------------------------------------------------------------
	
	dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.2f));
	dLight->GetTransform()->Rotate(math::ToRadians(-65), math::Vector3(1, 0, 0));
	
	
	AddToScene(go);
	AddToScene(dLight);


	SetAmbientLightColor(Color::White);
	SetAmbientLightIntensity(0.3f);
}
