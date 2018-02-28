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
}

void TestGame::Init()
{
	GameObject planeOBJ = GameObject();
	//TODO make RGB(0-255,0-255,0-255) (and HEX) color picking 
	m_root = GetRootObject();
	//m_camera = new Camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)800/(float)600, 0.01f, 1000.0f);
	
	//m_camera = &mainCamera;
	m_texture = new Texture(".\\res\\uv_checker.png");
	
	m_material = new Material(*m_texture, glm::vec3(0.3f, 0.3f, 0.3f), 8, 32);
	m_mesh = new Mesh(".\\res\\plane.obj");
	m_meshRenderer = new MeshRenderer(*m_mesh, *m_material);

	planeOBJ.AddComponent(m_meshRenderer);
	GetRootObject()->AddChild(planeOBJ);

	//m_shader = new PhongShader();
	directionalLight = DirectionalLight(BaseLight(glm::vec3(244.0f/255.0f, 150.0f/255.0f, 28.0f/255.0f), 1), glm::vec3(0, -1, -1));
	PointLight pLight1(BaseLight(glm::vec3(1, 0, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(3, 3, 0));
	PointLight pLight2(BaseLight(glm::vec3(0, 0, 1), 10), Attenuation(1, 0, 0), 10, glm::vec3(-3, 3, 0));

	pointLights[0] = pLight1;
	pointLights[1] = pLight2;
	//PointLight pLight3(BaseLight(glm::vec3(0, 1, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(3, 1, 0));
	//PointLight pLight4(BaseLight(glm::vec3(1, 1, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(-3, 1, 0));
	
	SpotLight sLight1(PointLight(BaseLight(glm::vec3(0, 1, 0), 20), Attenuation(1,0,0), 10, glm::vec3(0, 1, 3)), glm::vec3(0, -1, -10), cos(glm::radians(35.0f)));
	spotLights[0] = sLight1;
	//m_shader->SetAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	//m_shader->SetDirectionalLight(directionalLight);
	//m_shader->SetPointLights(pointLights, 2);
	//m_shader->SetSpotLights(spotLights, 1);
			
}

void TestGame::Input()
{
	double deltaTime = Time::GetDelta();
	/*if (Input::GetKeyDown(SDL_SCANCODE_UP))	
		m_camera->Translate(FORWARD, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
		m_camera->Translate(RIGHT, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
		m_camera->Translate(BACKWARD, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
		m_camera->Translate(LEFT , 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
		m_camera->Translate(UP, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
		m_camera->Translate(DOWN, 5 * deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
		cout << m_camera->GetForward()->x <<";" << m_camera->GetForward()->y << ";" << m_camera->GetForward()->z << ";" << endl;
		
		
				
	if (Input::GetKeyDown(SDL_SCANCODE_W))
		m_camera->RotateX(deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_S))
		m_camera->RotateX(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_A))
		m_camera->RotateY(deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_D))
		m_camera->RotateY(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_Q))
		m_camera->RotateZ(-deltaTime);
	if (Input::GetKeyDown(SDL_SCANCODE_E))
		m_camera->RotateZ(deltaTime);*/
}

void TestGame::Update()
{
	m_root->Update();
}
