#include "AnimationTestGame.h"

#include "../Utils/AssimpImporter.h"
#include "../GameComponents/FreeLook.h"
#include "../GameComponents/FreeMove.h"
#include "../GameComponents/Animator.h"
#include "../GameComponents/Lighting.h"
#include <iostream>

void AnimationTestGame::Init()
{
    auto cameraOBJ = new GameObject("camera");


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

	auto dLight = new GameObject("Light");
	dLight->AddComponent(new DirectionalLight(Color(Color::White), 0.2f));



    AssimpImporter importer;
    importer.LoadFile(GetPath("anim_cube.dae"), this);
    //Animator* a = go->GetChild(0)->GetChild(0)->GetComponent<Animator>();
    //std::cout << "Animator" << a << std::endl;
	//FindGameObject("Cube")->AddComponent(new FreeMove());
	//AddToScene(dLight);


}
