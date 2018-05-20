#include "TestGame.h"
#include <iostream>
#include "Core\Window.h"
#include "GameComponents\Lighting.h"
#include "GameComponents\MeshRenderer.h"
#include "GameComponents\FreeLook.h"
#include "GameComponents\FreeMove.h"
#include "Rendering\Mesh.h"

TestGame::TestGame() {}


void TestGame::Init()
{
	auto planeOBJ = new GameObject();
	auto cubeOBJ = new GameObject();
	auto cubeOBJ2 = new GameObject();
	auto dLight = new GameObject();
	auto pLight = new GameObject();
	auto sLight = new GameObject();
	auto cameraOBJ = new GameObject();

	Material* material1 = new Material();
	Texture* texture1 = new Texture(".\\res\\uv_checker.png");
	material1->AddTexture("diffuse", *texture1);
	material1->AddFloat("specularIntensity", 2);
	material1->AddFloat("specularExponent", 32);
	Mesh* mesh1 = new Mesh(".\\res\\plane.obj");
	MeshRenderer* meshRenderer = new MeshRenderer(*mesh1, *material1);
	planeOBJ->AddComponent(meshRenderer);

	dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.2f));
	dLight->GetTransform()->Rotate(math::ToRadians(-135.0f), math::Vector3(1, 0, 0));
	pLight->AddComponent(new PointLight(Color::Red, 1, Attenuation(1, 0, 0)));
	pLight->GetTransform()->SetPosition(math::Vector3(0, 1.5f, 0));
	pLight->GetComponent<PointLight>()->SetColor(Color::Green);


	sLight->AddComponent(new SpotLight(Color::Blue, 10, Attenuation(1, 0, 0), cos(math::ToRadians(45.0f))));
	sLight->GetTransform()->SetPosition(math::Vector3(-2, 1, 5));
	//sLight->GetTransform()->SetRotation(math::Quaternion(math::ToRadians(45.0f), math::Vector3(0, 0, 1)) * glm::angleAxis(math::ToRadians(90.0f), math::Vector3(0,1,0)));

	Material* material2 = new Material();
	Texture* texture2 = new Texture(".\\res\\texture.jpg");
	material2->AddTexture("diffuse", *texture2);
	material2->AddFloat("specularIntensity", 2);
	material2->AddFloat("specularExponent", 32);
	Mesh* mesh2 = new Mesh(".\\res\\cubeUV.obj");
	MeshRenderer* meshRenderer2 = new MeshRenderer(*mesh2, *material2);
	cubeOBJ->GetTransform()->SetPosition(math::Vector3(-5, 1, 0));
	cubeOBJ->GetTransform()->SetScale(math::Vector3(2, 1, 1));
	//cubeOBJ->GetTransform()->SetLocalRotation(angleAxis(math::ToRadians(-60.0f), math::Vector3(1, 1, 0)));
	cubeOBJ->AddComponent(meshRenderer2);

	cameraOBJ->AddComponent(new Camera(
		60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f));
	//cameraOBJ->AddComponent(new SpotLight(Color::Blue, 20, Attenuation(1, 0, 0), cos(math::ToRadians(45.0f))));
	cameraOBJ->GetTransform()->SetPosition(math::Vector3(-5, 3, 15));
	//cameraOBJ->GetTransform()->SetLocalRotation(math::Quaternion(math::ToRadians(-45.0f), math::Vector3(1, 0, 0)) /** math::Quaternion(math::ToRadians(180.0f), math::Vector3(0,1,0))*/);
	cameraOBJ->AddComponent(new FreeLook());
	cameraOBJ->AddComponent(new FreeMove());

	cubeOBJ2->AddComponent(new MeshRenderer(*new Mesh(".\\res\\cubeUV.obj"),
	                                        *new Material(*new Texture(".\\res\\uv_checker.png"), 2, 32)));
	cubeOBJ2->GetTransform()->SetPosition(math::Vector3(3, 0, 0));
	//cubeOBJ->GetTransform()->SetRotation(angleAxis(math::ToRadians(-30.0f), math::Vector3(0, 1, 0)));

	AddToScene(planeOBJ);
	AddToScene(cameraOBJ);
	AddToScene(cubeOBJ);
	cubeOBJ->AddChild(pLight);
	cubeOBJ->AddChild(cubeOBJ2);

	AddToScene(dLight);
	AddToScene(sLight);
	//pLight->AddChild(cubeOBJ);
}
