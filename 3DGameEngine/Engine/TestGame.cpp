#include "TestGame.h"
#include "GameComponents\Lighting.h"

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
    auto dLight = new GameObject();
    auto pLight = new GameObject();
    auto sLight = new GameObject();
    //m_root = GetRootObject();
    m_texture = new Texture(".\\res\\uv_checker.png");

    m_material = new Material(*m_texture, 2, 32);
    m_mesh = new Mesh(".\\res\\plane.obj");
    m_meshRenderer = new MeshRenderer(*m_mesh, *m_material);
    planeOBJ->AddComponent(m_meshRenderer);

    dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.15f));
    dLight->GetTransform()->SetRotation(angleAxis(glm::radians(-135.0f), glm::vec3(1, 0, 0)));

    pLight->AddComponent(new PointLight(Color::Red(), 1, Attenuation(1, 0, 0)));
    pLight->GetTransform()->SetPosition(glm::vec3(5, 1, 0));

    sLight->AddComponent(new SpotLight(Color::Blue(), 1, Attenuation(1, 0, 0), cos(glm::radians(45.0f))));
    sLight->GetTransform()->SetPosition(glm::vec3(0, 1, 0));
    sLight->GetTransform()->SetRotation(angleAxis(glm::radians(-60.0f), glm::vec3(1, 0, 0)));

    m_texture2 = new Texture(".\\res\\texture.jpg");
    m_material2 = new Material(*m_texture2, 2, 32);
    m_mesh2 = new Mesh(".\\res\\cubeUV.obj");
    m_meshRenderer2 = new MeshRenderer(*m_mesh2, *m_material2);
    cubeOBJ->GetTransform()->SetPosition(glm::vec3(-2, 2, 0));
    cubeOBJ->GetTransform()->SetRotation(angleAxis(glm::radians(-60.0f), glm::vec3(1, 1, 0)));
    cubeOBJ->AddComponent(m_meshRenderer2);


    m_root->AddChild(planeOBJ);

    m_root->AddChild(dLight);
    m_root->AddChild(pLight);
    m_root->AddChild(sLight);
    m_root->AddChild(cubeOBJ);
}

void TestGame::Input()
{
}

void TestGame::Update()
{
    m_root->Update();
}
