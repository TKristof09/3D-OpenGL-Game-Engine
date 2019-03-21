#include "PhysicsTestGame.h"
#include "3DMath/3DMath.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Texture.h"
#include "../Rendering/Material.h"
#include "../GameComponents/MeshRenderer.h"
#include "../GameComponents/FreeMove.h"
#include "../GameComponents/FreeLook.h"
#include "../Core/Window.h"
#include "../GameComponents/Lighting.h"
#include "../Utils/FileLoader.h"

#include "../Physics/PhysicsEngine.h"
#include "../Physics/ConvexHull.h"
#include "../Physics/Box.h"
#include "../Core/Input.h"

class TestP :public GameComponent
{
public:
	void Update() override
	{
		Rigidbody* rb = GetGameObject()->GetComponent<Rigidbody>();
		if(Input::GetKeyDown(SDL_SCANCODE_F))
		{
			rb->AddForce(-rb->GetBtPointer()->getGravity());
		}
		if (Input::GetKeyDown(SDL_SCANCODE_I))
		{
			rb->GetBtPointer()->applyCentralImpulse(impulse.ToBtVector3());
		}
	};
	math::Vector3 force = math::Vector3(0);
	math::Vector3 impulse = math::Vector3(0);

};

void PhysicsTestGame::Init()
{
    auto sphereOBJ1 = new GameObject(); sphereOBJ1->name = "1";
    auto sphereOBJ2 = new GameObject(); sphereOBJ2->name = "2";
    auto sphereOBJ3 = new GameObject(); sphereOBJ3->name = "3";
    auto cameraOBJ = new GameObject();
    auto dLight = new GameObject();
    auto trigger = new GameObject();

    //--------------------------------------------------------------------------------------------------------------------------------------
    //Camera
    //--------------------------------------------------------------------------------------------------------------------------------------

    cameraOBJ->AddComponent(new Camera(
        60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
    cameraOBJ->GetTransform()->SetPosition(math::Vector3(0, 3, 15));
    cameraOBJ->AddComponent(new FreeLook());
    cameraOBJ->AddComponent(new FreeMove());
    cameraOBJ->AddComponent(new AudioListener());

    //--------------------------------------------------------------------------------------------------------------------------------------
    //Objects
    //--------------------------------------------------------------------------------------------------------------------------------------



    Material* material1 = new Material();
    material1->AddVector3("color", Color::White.ToVector3());
    Mesh* mesh1 = new Mesh(GetPath("cube.obj"));
    MeshRenderer* meshRenderer1 = new MeshRenderer(mesh1, material1);
    sphereOBJ1->AddComponent(meshRenderer1);

    Collider* box = new Box(math::Vector3(1));
    sphereOBJ1->GetTransform()->SetPosition(math::Vector3(-5, 10, 0));
    sphereOBJ1->GetTransform()->Rotate(math::ToRadians(45.f), math::Vector3(0, 1, 0));
    sphereOBJ1->AddComponent(box);
    sphereOBJ1->AddComponent(new Rigidbody(1.0f));

    TestP* test = new TestP();
    test->force = math::Vector3(0, 20, 0);
    test->impulse = math::Vector3(0, 1, 0);
    sphereOBJ1->AddComponent(test);
    TestP* test2 = new TestP();
    test2->force = math::Vector3(0, 20, 0);
    test2->impulse = math::Vector3(0, 1, 0);
    sphereOBJ2->AddComponent(test2);



    Material* material2 = new Material();
    Mesh* mesh2 = new Mesh(GetPath("cube.obj"));
    MeshRenderer* meshRenderer2 = new MeshRenderer(mesh1, material2);
    sphereOBJ2->AddComponent(meshRenderer2);
    sphereOBJ2->GetTransform()->SetPosition(math::Vector3(5, 10, 0));

    Collider* box2 = new Box(math::Vector3(1));
    sphereOBJ2->AddComponent(box2);
    Rigidbody* rb = new Rigidbody(100000.0f);
    sphereOBJ2->AddComponent(rb);


    Material* material3 = new Material();

    material3->AddVector3("color", Color::Red.ToVector3());
    Mesh* mesh3 = new Mesh(GetPath("cube.obj"));
    MeshRenderer* meshRenderer3 = new MeshRenderer(mesh1, material3);
    sphereOBJ3->AddComponent(meshRenderer3);
    sphereOBJ3->GetTransform()->SetPosition(math::Vector3(0, -5, 0));
    sphereOBJ3->GetTransform()->Rotate(math::Quaternion(45, math::Vector3(0, 1, 0)));

    Collider* cHull = new ConvexHull(*mesh3);
    sphereOBJ3->AddComponent(new ConvexHull(*mesh1));
    sphereOBJ3->AddComponent(new Rigidbody(0));


    Collider* triggerColl = new Box(math::Vector3(10, 0.5f, 10));
    trigger->AddComponent(new TriggerCollider(triggerColl));
    TextureConfig normal;
    normal.path = GetPath("rustediron2_normal.png");
    material1->AddTexture("albedo", new Texture(normal));
    trigger->AddComponent(new MeshRenderer(mesh1, material1));
    trigger->GetTransform()->SetScale(math::Vector3(10, 10, 10));
    //--------------------------------------------------------------------------------------------------------------------------------------
    //Lights
    //--------------------------------------------------------------------------------------------------------------------------------------
    dLight->AddComponent(new DirectionalLight(Color(244.0f, 150.0f, 28.0f), 0.2f));
    //dLight->GetTransform()->SetPosition(math::Vector3(2, 2, -2));
    //dLight->GetTransform()->SetScale(math::Vector3(0.2f));
    dLight->GetTransform()->Rotate(math::ToRadians(-135.0f), math::Vector3(1, 0, 0));


    AddToScene(sphereOBJ1);
    AddToScene(sphereOBJ2);
    AddToScene(sphereOBJ3);
    AddToScene(cameraOBJ);
    AddToScene(dLight);
    AddToScene(trigger);

}
