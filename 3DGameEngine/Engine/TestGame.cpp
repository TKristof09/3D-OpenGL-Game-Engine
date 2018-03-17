#include "TestGame.h"
#include "GameComponents\Lighting.h"
#include "Core\Window.h"
#include <iostream>
#include "GameComponents\FreeLook.h"

TestGame::TestGame()
    : m_root(nullptr),
      m_meshRenderer(nullptr),
      m_meshRenderer2(nullptr),
      m_mesh(nullptr),
      m_mesh2(nullptr),
      m_material(nullptr),
      m_material2(nullptr),
      m_texture(nullptr),
      m_texture2(nullptr)
{
}


TestGame::~TestGame()
{
    delete m_meshRenderer;
    delete m_meshRenderer2;
    delete m_mesh;
    delete m_mesh2;
    delete m_material;
    delete m_material2;
    delete m_texture;
    delete m_texture2;
}

void TestGame::Init()
{
    m_root = GetRootObject();
    auto planeOBJ = new GameObject();
    auto cubeOBJ = new GameObject();
    auto cubeOBJ2 = new GameObject();
    auto dLight = new GameObject();
    auto pLight = new GameObject();
    auto sLight = new GameObject();
    auto cameraOBJ = new GameObject();
    //m_root = GetRootObject();

    m_material = new Material();
    m_texture = new Texture(".\\res\\uv_checker.png");
    m_material->AddTexture("diffuse", *m_texture);
    m_material->AddFloat("specularIntensity", 2);
    m_material->AddFloat("specularExponent", 32);
    m_mesh = new Mesh(".\\res\\plane.obj");
    m_meshRenderer = new MeshRenderer(*m_mesh, *m_material);
    planeOBJ->AddComponent(m_meshRenderer);

    dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.2f));
    dLight->GetTransform()->SetRotation(glm::angleAxis(glm::radians(-135.0f), glm::vec3(1, 0, 0)));
    pLight->AddComponent(new PointLight(Color::Red(), 1, Attenuation(1, 0, 0)));
    pLight->GetTransform()->SetPosition(glm::vec3(0, 1.5f, 0));
    pLight->GetComponent<PointLight>()->SetColor(Color::Green());
    

    sLight->AddComponent(new SpotLight(Color::Blue(), 10, Attenuation(1, 0, 0), cos(glm::radians(45.0f))));
    sLight->GetTransform()->SetPosition(glm::vec3(-2, 1, 5));
    //sLight->GetTransform()->SetRotation(glm::angleAxis(glm::radians(45.0f), glm::vec3(0, 0, 1)) * glm::angleAxis(glm::radians(90.0f), glm::vec3(0,1,0)));

    m_material2 = new Material();
    m_texture2 = new Texture(".\\res\\texture.jpg");
    m_material2->AddTexture("diffuse", *m_texture2);
    m_material2->AddFloat("specularIntensity", 2);
    m_material2->AddFloat("specularExponent", 32);
    m_mesh2 = new Mesh(".\\res\\cubeUV.obj");
    m_meshRenderer2 = new MeshRenderer(*m_mesh2, *m_material2);
    cubeOBJ->GetTransform()->SetPosition(glm::vec3(-5, 1, 0));
    cubeOBJ->GetTransform()->SetScale(glm::vec3(2, 1, 1));
    //cubeOBJ->GetTransform()->SetLocalRotation(angleAxis(glm::radians(-60.0f), glm::vec3(1, 1, 0)));
    cubeOBJ->AddComponent(m_meshRenderer2);
    
    cameraOBJ->AddComponent(new Camera(60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.01f, 1000.0f));
    //cameraOBJ->AddComponent(new SpotLight(Color::Blue(), 20, Attenuation(1, 0, 0), cos(glm::radians(45.0f))));
    cameraOBJ->GetTransform()->SetPosition(glm::vec3(-5, 3, 15));
    //cameraOBJ->GetTransform()->SetLocalRotation(glm::angleAxis(glm::radians(-45.0f), glm::vec3(1, 0, 0)) /** glm::angleAxis(glm::radians(180.0f), glm::vec3(0,1,0))*/);
    cameraOBJ->AddComponent(new FreeLook());
    
    cubeOBJ2->AddComponent(new MeshRenderer(*new Mesh(".\\res\\cubeUV.obj"), *new Material(*new Texture(".\\res\\uv_checker.png"), 2, 32)));
    cubeOBJ2->GetTransform()->SetPosition(glm::vec3(3, 0, 0));
    //cubeOBJ->GetTransform()->SetRotation(angleAxis(glm::radians(-30.0f), glm::vec3(0, 1, 0)));

    m_root->AddChild(planeOBJ);
    m_root->AddChild(cameraOBJ);
    m_root->AddChild(cubeOBJ);
    cubeOBJ->AddChild(pLight);
    cubeOBJ->AddChild(cubeOBJ2);

    m_root->AddChild(dLight);
    m_root->AddChild(sLight);
    //pLight->AddChild(cubeOBJ);
}

