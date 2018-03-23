#include "TestGame.h"
#include "GameComponents\Lighting.h"
#include "Core\Window.h"
#include <iostream>
#include "Rendering\Mesh.h"
#include "GameComponents\FreeLook.h"
#include "GameComponents\MeshRenderer.h"

TestGame::TestGame()
{
}


TestGame::~TestGame()
{
    
}

void TestGame::Init()
{
    auto planeOBJ = new GameObject();
//    auto cubeOBJ = new GameObject();
//    auto cubeOBJ2 = new GameObject();
//    auto dLight = new GameObject();
//    auto pLight = new GameObject();
//    auto sLight = new GameObject();
    auto cameraOBJ = new GameObject();
    //m_root = GetRootObject();

    Material* material = new Material();
    Texture* texture = new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\uv_checker.png");
    material->AddTexture("diffuse", *texture);
    material->AddFloat("specularIntensity", 2);
    material->AddFloat("specularExponent", 32);
    Mesh* mesh = new Mesh("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\plane.obj");
    MeshRenderer* meshRenderer = new MeshRenderer(*mesh, *material);
    planeOBJ->AddComponent(meshRenderer);
    std::cout << math::ToString(planeOBJ->GetTransform()->GetWorldPosition()) << std::endl;
    /*
    dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.2f));
    dLight->GetTransform()->Rotate(math::ToRadians(-135.0f), math::Vector3(1, 0, 0));
    
    pLight->AddComponent(new PointLight(Color::Red(), 1, Attenuation(1, 0, 0)));
    pLight->GetTransform()->SetPosition(math::Vector3(0, 1.5f, 0));
    pLight->GetComponent<PointLight>()->SetColor(Color::Green());
    

    sLight->AddComponent(new SpotLight(Color::Blue(), 10, Attenuation(1, 0, 0), cos(math::ToRadians(45.0f))));
    sLight->GetTransform()->SetPosition(math::Vector3(-2, 1, 5));
    //sLight->GetTransform()->SetRotation(glm::angleAxis(math::ToRadians(45.0f), math::Vector3(0, 0, 1)) * glm::angleAxis(math::ToRadians(90.0f), math::Vector3(0,1,0)));

    Material* material2 = new Material();
    Texture* texture2 = new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\texture.jpg");
    material2->AddTexture("diffuse", *texture2);
    material2->AddFloat("specularIntensity", 2);
    material2->AddFloat("specularExponent", 32);
    Mesh* mesh2 = new Mesh("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\cubeUV.obj");
    MeshRenderer* meshRenderer2 = new MeshRenderer(*mesh2, *material2);
    cubeOBJ->GetTransform()->SetPosition(math::Vector3(-5, 1, 0));
    cubeOBJ->GetTransform()->SetScale(math::Vector3(2, 1, 1));
    cubeOBJ->GetTransform()->SetLocalRotation(angleAxis(math::ToRadians(-60.0f), math::Vector3(1, 1, 0)));
    cubeOBJ->AddComponent(meshRenderer2);
    */
    cameraOBJ->AddComponent(new Camera(60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f));
    //cameraOBJ->AddComponent(new SpotLight(Color::Blue(), 20, Attenuation(1, 0, 0), cos(math::ToRadians(45.0f))));
    cameraOBJ->GetTransform()->SetPosition(math::Vector3(-5, 3, 15));
    cameraOBJ->GetTransform()->Rotate(math::ToRadians(-30.0f), math::Vector3(1, 0, 0));
    cameraOBJ->AddComponent(new FreeLook());
    
//    cubeOBJ2->AddComponent(new MeshRenderer(*new Mesh("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\cubeUV.obj"), *new Material(*new Texture("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\uv_checker.png"), 2, 32)));
//    cubeOBJ2->GetTransform()->SetPosition(math::Vector3(3, 0, 0));
//    cubeOBJ->GetTransform()->SetRotation(angleAxis(math::ToRadians(-30.0f), math::Vector3(0, 1, 0)));

    AddToScene(planeOBJ);
    AddToScene(cameraOBJ);
//    AddToScene(cubeOBJ);
//    cubeOBJ->AddChild(pLight);
//    cubeOBJ->AddChild(cubeOBJ2);
//
//    AddToScene(dLight);
//    AddToScene(sLight);
//    pLight->AddChild(cubeOBJ);
}

