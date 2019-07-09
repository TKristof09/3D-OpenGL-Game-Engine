#include "AssimpTestGame.h"

#include "../Utils/AssimpImporter.h"
#include "../GameComponents/FreeLook.h"
#include "../GameComponents/FreeMove.h"
#include "../Core/Window.h"
#include "../Utils/OBJloader.h"
#include "../Utils/FileLoader.h"
#include "../GameComponents/Lighting.h"
#include "../Rendering/RadianceHDRTexture.h"
void AssimpTestGame::Init()
{
	auto cameraOBJ = new GameObject("camera");
	auto sLight = new GameObject("sLight");


	//--------------------------------------------------------------------------------------------------------------------------------------
	//Camera
	//--------------------------------------------------------------------------------------------------------------------------------------

	cameraOBJ->AddComponent(new Camera(
		60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
	cameraOBJ->GetTransform()->SetPosition(math::Vector3(0, 0, 5));
	cameraOBJ->AddComponent(new FreeLook());
	cameraOBJ->AddComponent(new FreeMove());
    cameraOBJ->AddComponent(new AudioListener());
	AddToScene(cameraOBJ);


	AssimpImporter importer;
	GameObject* go = importer.LoadFile(GetPath("cubeUV.fbx"), this);
	//go->GetTransform()->Rotate(math::ToRadians(-90.0f), math::Vector3(1, 0, 0));
	//go->GetTransform()->SetScale(math::Vector3(10, 10, 10));
    //go->GetTransform()->SetScale(math::Vector3(10, 1, 10));
	MeshRenderer* mr = go->GetChild(0)->GetComponent<MeshRenderer>();
	//go->GetChild(0)->GetTransform()->SetScale(math::Vector3(2));
	Material* material1 = mr->material;
	TextureConfig albedo;
	albedo.path = GetPath("rustediron2_basecolor.png");
	TextureConfig normal;
	normal.path = GetPath("rustediron2_normal.png");
	TextureConfig metallic;
	metallic.path = GetPath("rustediron2_metallic.png");
	TextureConfig roughness;
	roughness.path = GetPath("rustediron2_roughness.png");
	material1->AddTexture("albedo", new Texture(albedo));
	material1->AddTexture("normal", new Texture(normal));
	material1->AddTexture("metallic", new Texture(metallic));
	material1->AddTexture("roughness", new Texture(roughness));
    //--------------------------------------------------------------------------------------------------------------------------------------
	//Lights
	//--------------------------------------------------------------------------------------------------------------------------------------

	sLight->AddComponent(new SpotLight(Color::Red, 1.0f, Attenuation(1,0,0), math::ToRadians(30)));
	sLight->GetTransform()->Translate(math::Vector3(0, 0, -2));
//	sLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.6f));
	sLight->GetTransform()->Rotate(math::ToRadians(65), math::Vector3(1, 0, 0));
//	sLight->GetTransform()->Translate(math::Vector3(2, 2, 0));

	AddToScene(go);
	//AddToScene(sLight);

}
