#include <iostream>
#include "Core.h"
#include "Input.h"
#include "Timer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture.h"
#include "BasicShader.h"
#include "PhongShader.h"
#include "Material.h"
#include "BaseLight.h"
#include "DirectionalLight.h"

#include <glm\ext.hpp>

#ifdef __cplusplus
extern "C"
#endif

const int FPS_CAP = 60;
const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);


void Update()
{
	// Just for future stuff
}


int main(int argc, char *argv[])
{

	bool capFPS = true;

	Timer timer;	


	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;


	Core display(1024, 720, "3D Game Engine");
	std::cout << "Hello world" << std::endl;
	
	Camera camera(glm::vec3(0, 0, -10), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), 70.0f, * display.GetWidth() / (float)*display.GetHeight(), 0.01f, 1000.0f);

	Texture texture(".\\res\\uv_checker.png");
	Material material(texture, glm::vec3(1,1,1), 2, 32);
	Mesh mesh(".\\res\\cubeUV.obj");

	Transform transform;

	PhongShader phongShader;


	BaseLight baseLight(glm::vec3(1, 1, 1), 1.0f);
	DirectionalLight directionalLight(baseLight, glm::vec3(0, 0, 1));

	
	
	float counter = 0.0f;

	cout << glm::to_string(camera.GetLeft()) << endl;
	cout << glm::to_string(camera.GetRight()) << endl;

	while (!display.IsClosed())
	{
		// Delta time calculation
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;
				
		
		float sinCounter = sin(counter);
		float cosCounter = cos(counter);

		display.Clear(0.5, 0.5, 0.5, 1.0f);

		glm::vec3 rot = *transform.GetRotation();
		rot.y = counter * 3;
		//transform.SetRotation(rot);
		
		// Set up inputs here
		// TODO make better input handling

		if (Input::GetKeyDown(SDL_SCANCODE_UP))
			camera.Translate(FORWARD, 5 * deltaTime);
			//camera.GetPos()->z = camera.GetPos()->z + 5 * deltaTime;
		if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
			camera.Translate(RIGHT, 5 * deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
			camera.Translate(BACKWARD, 5 * deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
			camera.Translate(LEFT , 5 * deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
			camera.Translate(UP, 5 * deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
			camera.Translate(DOWN, 5 * deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
			cout << camera.GetForward()->x <<";" << camera.GetForward()->y << ";" << camera.GetForward()->z << ";" << endl;


		
		if (Input::GetKeyDown(SDL_SCANCODE_W))
			camera.RotateX(deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_S))
			camera.RotateX(-deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_A))
			camera.RotateY(deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_D))
			camera.RotateY(-deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_Q))
			camera.RotateZ(-deltaTime);
		if (Input::GetKeyDown(SDL_SCANCODE_E))
			camera.RotateZ(deltaTime);

	
		Update(); // TODO maybe not right place for this
		//material.SetTexture(texture);
		//texture.Bind(0);
		phongShader.SetAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
		phongShader.SetDirectionalLight(directionalLight);
		phongShader.Bind();
		phongShader.Update(transform, camera, material);
		mesh.Draw();
		display.Update();
		
		if (capFPS && timer.GetTicks() < 1000 / FPS_CAP)
		{
			SDL_Delay((1000 / FPS_CAP) - timer.GetTicks());
		}

		counter += 0.005f;
	}

	return 0;
}
