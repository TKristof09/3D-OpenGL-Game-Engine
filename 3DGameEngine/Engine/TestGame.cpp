#include "TestGame.h"
#include "Core\Time.h"
#include "GameComponents\Lighting.h"

//extern Camera mainCamera;

TestGame::TestGame()
{

}


TestGame::~TestGame()
{
	delete m_mesh;
	//delete m_shader;
	//delete m_camera;
	delete m_texture;
	delete m_material;
	delete m_meshRenderer;
	delete meshRenderer2;
	delete material2;
	delete mesh2;
}

void TestGame::Init()
{
	GameObject* planeOBJ = new GameObject();
	GameObject* cubeOBJ = new GameObject();
    GameObject* dLight = new GameObject();
    GameObject* pLight = new GameObject();
    GameObject* sLight = new GameObject();
	m_root = GetRootObject();
	m_texture = new Texture(/*".\\res\\uv_checker.png"*/);
	
	m_material = new Material(*m_texture, glm::vec3(0.3f, 0.3f, 0.3f), 2, 32);
	m_mesh = new Mesh(".\\res\\plane.obj");
	m_meshRenderer = new MeshRenderer(*m_mesh, *m_material);
    planeOBJ->AddComponent(m_meshRenderer);

    dLight->AddComponent(new DirectionalLight(glm::vec3(244.0f / 255.0f, 150.0f / 255.0f, 28.0f / 255.0f), 0.2f));
    dLight->GetTransform()->SetRotation(glm::vec3(0, -1, 5));

    pLight->AddComponent(new PointLight(glm::vec3(1, 0, 0), 1, Attenuation(1, 0, 0)));
    pLight->GetTransform()->SetPosition(glm::vec3(-3, 2, -5));

    sLight->AddComponent(new SpotLight(glm::vec3(0, 0, 1), 1, Attenuation(1, 0, 0), cos(glm::radians(45.0f))));
    sLight->GetTransform()->SetPosition(glm::vec3(-5, 3.5f, -7));
    sLight->GetTransform()->SetRotation(glm::vec3(1, -0.4f, 1));

	material2 = new Material(*m_texture, glm::vec3(0.3f, 0.3f, 0.3f), 2, 32);
	mesh2 = new Mesh(".\\res\\cubeUV.obj");
	meshRenderer2 = new MeshRenderer(*mesh2, *material2);
	cubeOBJ->GetTransform()->SetPosition(glm::vec3(-5, 2, -7));
	cubeOBJ->AddComponent(meshRenderer2);


    m_root->AddChild(planeOBJ);
    
    //m_root->AddChild(dLight);
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
