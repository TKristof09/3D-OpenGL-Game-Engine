#include "TestGame.h"
#include "Core\Time.h"

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
	GameObject planeOBJ = GameObject();
	GameObject cubeOBJ = GameObject();
	m_root = GetRootObject();
	//m_camera = new Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)800/(float)600, 0.01f, 1000.0f);
	
	//m_camera = &mainCamera;
	m_texture = new Texture(".\\res\\uv_checker.png");
	
	m_material = new Material(*m_texture, glm::vec3(0.3f, 0.3f, 0.3f), 2, 32);
	m_mesh = new Mesh(".\\res\\plane.obj");
	m_meshRenderer = new MeshRenderer(*m_mesh, *m_material);
	planeOBJ.AddComponent(m_meshRenderer);

	material2 = new Material(*m_texture, glm::vec3(0.3f, 0.3f, 0.3f), 2, 32);
	mesh2 = new Mesh(".\\res\\cubeUV.obj");
	meshRenderer2 = new MeshRenderer(*mesh2, *material2);
	cubeOBJ.GetTransform()->SetPosition(glm::vec3(0, 3, 0));
	cubeOBJ.AddComponent(meshRenderer2);


    m_root->AddChild(planeOBJ);
    //m_root->AddChild(cubeOBJ);
				
}

void TestGame::Input()
{
		
}

void TestGame::Update()
{
	m_root->Update();
}
