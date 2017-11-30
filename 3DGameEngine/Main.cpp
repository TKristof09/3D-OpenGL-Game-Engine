#include <iostream>
#include "Core.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture.h"
#include "BasicShader.h"


#include <glm\ext.hpp>

int main(int argc, char *argv[])
{
	
	const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
	const glm::vec3 Y_AXIS = glm::vec3(0, 1, 0);
	const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);


	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;


	Core display(800, 600, "3D Game Engine");
	std::cout << "Hello world" << std::endl;
	
	Camera camera(glm::vec3(0, 0, -10), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), 70.0f, * display.GetWidth() / (float)*display.GetHeight(), 0.01f, 1000.0f);

	//Vertex vertices[] = { Vertex(glm::vec3(-1, -1, 0), glm::vec2(0, 0)),
	//					Vertex(glm::vec3(0, 1, 0), glm::vec2(0.5f, 0)),
	//					Vertex(glm::vec3(1, -1, 0), glm::vec2(1.0f, 0)),
	//					Vertex(glm::vec3(0, -1, 1), glm::vec2(0.5f, 1.0f)) };

	//unsigned int indices[] = { 3,1,0,
	//							2,1,3,
	//							0,1,2,
	//							0,2,3 };

	//Mesh mesh2(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	Mesh mesh(".\\res\\cubeUV.obj");

	Transform transform;

	BasicShader shader;

	Texture texture(".\\res\\texture.jpg");
	
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

		display.Clear(0.1f, 0.3f, 0.5f, 1.0f);

		// Set up inputs here
		// TODO consider switch statement

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

	
		//cout << to_string(*camera.GetForward()) << endl;
		
		shader.Bind();
		shader.Update(transform, camera);
		texture.Bind(0);
		//mesh2.Draw();
		mesh.Draw();
		display.Update();
		
		

		counter += 0.005f;
	}

	return 0;
}
