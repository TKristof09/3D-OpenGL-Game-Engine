//#include <iostream>
//#include "Core\Core.h"
//#include "Core\Input.h"
//#include "Core\Timer.h"
//#include "Core\Transform.h"
//#include "Rendering\Mesh.h"
//#include "Rendering\Shader.h"
//#include "Rendering\Texture.h"
//#include "Rendering\BasicShader.h"
//#include "Rendering\PhongShader.h"
//#include "Rendering\Material.h"
//#include "Rendering\Lighting\BaseLight.h"
//#include "Rendering\Lighting\DirectionalLight.h"
//#include "Camera.h"
//
//#include <glm\ext.hpp>
//
//#ifdef __cplusplus
//extern "C"
//#endif
//
//const int FPS_CAP = 60;
//const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
//const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
//const glm::vec3 Z_AXIS = glm::vec3(0, 0, -1);
//
//
//void Update()
//{
//	// Just for future stuff
//}
//
//
//int main(int argc, char *argv[])
//{
//
//	bool capFPS = true;
//
//	Timer timer;	
//
//
//	Uint64 NOW = SDL_GetPerformanceCounter();
//	Uint64 LAST = 0;
//	double deltaTime = 0;
//
//
//	Core display(1024, 720, "3D Game Engine", FPS_CAP);
//	std::cout << "Hello world" << std::endl;
//	
//	Camera camera(glm::vec3(0, 3, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 70.0f, (float)*display.GetWidth() / (float)*display.GetHeight(), 0.01f, 1000.0f);
//
//	Texture texture;
//	Material material(texture, glm::vec3(0.3f, 0.3f, 0.3f), 2, 256);
//	Mesh mesh(".\\res\\plane.obj");
//
//	Transform transform;
//
//	PhongShader phongShader;
//	DirectionalLight directionalLight(BaseLight(glm::vec3(244.0f/255.0f, 150.0f/255.0f, 28.0f/255.0f), 1), glm::vec3(0, -1, -1));
//	PointLight pLight1(BaseLight(glm::vec3(1, 0, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(3, 3, 0));
//	PointLight pLight2(BaseLight(glm::vec3(0, 0, 1), 10), Attenuation(1, 0, 0), 10, glm::vec3(-3, 3, 0));
//	//PointLight pLight3(BaseLight(glm::vec3(0, 1, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(3, 1, 0));
//	//PointLight pLight4(BaseLight(glm::vec3(1, 1, 0), 10), Attenuation(1, 0, 0), 10, glm::vec3(-3, 1, 0));
//
//	SpotLight sLight1(PointLight(BaseLight(glm::vec3(1, 1, 0.2f), 20), Attenuation(1,0,0), 10, glm::vec3(0, 1, 3)), glm::vec3(0, -1, -10), cos(glm::radians(35.0f)));
//	
//		
//	float counter = 0.0f;
//
//	//cout << glm::to_string(camera.GetLeft()) << endl;
//	//cout << glm::to_string(camera.GetRight()) << endl;
//	float pi = 3.141592653589793f;
//	while (!display.IsClosed())
//	{
//		// Delta time calculation
//		LAST = NOW;
//		NOW = SDL_GetPerformanceCounter();
//		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;
//				
//		
//		float sinCounter = sin(counter);
//		float cosCounter = cos(counter);
//
//		display.Clear(0, 0, 0, 1.0f);
//
//		glm::vec3 rot = *transform.GetRotation();
//		rot.y = counter;
//		//transform.SetRotation(rot);
//
//		directionalLight.SetDirection(glm::vec3(0, sin(counter + pi/2), sin(counter) ));
//		pLight1.SetPosition(glm::vec3(sin(counter * 10) * 5, 3, cos(counter * 10) * 5));
//		pLight2.SetPosition(glm::vec3(-sin(counter * 10) * 5, 3, cos(counter * 10) * 5));
//		//pLight2.SetPosition(glm::vec3(sin(counter * 10 + pi * 0.5f) * 5, 3, cos(counter * 10 + pi * 0.5f) * 5));
//		//cout << glm::to_string(*pLight1.GetPosition()) << endl;
//		//pLight3.SetPosition(glm::vec3(sin(counter * 10 + pi) * 5, 3, cos(counter * 10 + pi) * 5));
//		//pLight4.SetPosition(glm::vec3(sin(counter * 10 + pi * 1.5f) * 5, 3, cos(counter * 10 + pi * 1.5f) * 5));
//		//cout << glm::to_string(*pLight2.GetPosition()) << endl;
//		
//		// Set up inputs here
//
//
//		if (Input::GetKeyDown(SDL_SCANCODE_UP))
//			camera.Translate(FORWARD, 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
//			camera.Translate(RIGHT, 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
//			camera.Translate(BACKWARD, 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
//			camera.Translate(LEFT , 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
//			camera.Translate(UP, 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
//			camera.Translate(DOWN, 5 * deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
//			cout << camera.GetForward()->x <<";" << camera.GetForward()->y << ";" << camera.GetForward()->z << ";" << endl;
//
//
//		
//		if (Input::GetKeyDown(SDL_SCANCODE_W))
//			camera.RotateX(deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_S))
//			camera.RotateX(-deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_A))
//			camera.RotateY(deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_D))
//			camera.RotateY(-deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_Q))
//			camera.RotateZ(-deltaTime);
//		if (Input::GetKeyDown(SDL_SCANCODE_E))
//			camera.RotateZ(deltaTime);
//
//		Update(); // TODO maybe not right place for this
//		
//		phongShader.SetAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
//		phongShader.SetDirectionalLight(directionalLight);
//		PointLight pointLightArray[] = { pLight1, pLight2 };
//		phongShader.SetPointLights(pointLightArray, 2);
//		SpotLight spotLightArray[] = { sLight1 };
//		phongShader.SetSpotLights(spotLightArray, 1);
//		
//		phongShader.Bind();
//		phongShader.Update(transform, camera, material);
//		
//		mesh.Draw();
//		display.Update();
//		
//		if (capFPS && timer.GetTicks() < 1000 / FPS_CAP)
//		{
//			SDL_Delay((1000 / FPS_CAP) - timer.GetTicks());
//		}
//
//		counter += 0.005f;
//	}
//
//	return 0;
//}

#include "Core\CoreEngine.h"
#include "TestGame.h"

#ifdef __cplusplus
	extern "C"
#endif

int main(int argc, char *argv[])
{
	TestGame testGame;
	Game* game = &testGame;
	CoreEngine engine(800, 600, 60, game);
	engine.CreateWindow("3D Game Engine");
	engine.Start();

	return 0;
}
